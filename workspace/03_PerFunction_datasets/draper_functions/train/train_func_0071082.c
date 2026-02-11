slaveTryPartialResynchronization(int fd, int read_reply) {
    char *psync_runid;
    char psync_offset[32];
    sds reply;


    if (!read_reply) {


        server.repl_master_initial_offset = -1;

        if (server.cached_master) {
            psync_runid = server.cached_master->replrunid;
            snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
            redisLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
        } else {
            redisLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
            psync_runid = "?";
            memcpy(psync_offset,"-1",3);
        }


        reply = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PSYNC",psync_runid,psync_offset,NULL);
        if (reply != NULL) {
            redisLog(REDIS_WARNING,"Unable to send PSYNC to master: %s",reply);
            sdsfree(reply);
            aeDeleteFileEvent(server.el,fd,AE_READABLE);
            return PSYNC_WRITE_ERROR;
        }
        return PSYNC_WAIT_REPLY;
    }


    reply = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
    if (sdslen(reply) == 0) {


        sdsfree(reply);
        return PSYNC_WAIT_REPLY;
    }

    aeDeleteFileEvent(server.el,fd,AE_READABLE);

    if (!strncmp(reply,"+FULLRESYNC",11)) {
        char *runid = NULL, *offset = NULL;


        runid = strchr(reply,' ');
        if (runid) {
            runid++;
            offset = strchr(runid,' ');
            if (offset) offset++;
        }
        if (!runid || !offset || (offset-runid-1) != REDIS_RUN_ID_SIZE) {
            redisLog(REDIS_WARNING,
                "Master replied with wrong +FULLRESYNC syntax.");


            memset(server.repl_master_runid,0,REDIS_RUN_ID_SIZE+1);
        } else {
            memcpy(server.repl_master_runid, runid, offset-runid-1);
            server.repl_master_runid[REDIS_RUN_ID_SIZE] = '\0';
            server.repl_master_initial_offset = strtoll(offset,NULL,10);
            redisLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
                server.repl_master_runid,
                server.repl_master_initial_offset);
        }

        replicationDiscardCachedMaster();
        sdsfree(reply);
        return PSYNC_FULLRESYNC;
    }

    if (!strncmp(reply,"+CONTINUE",9)) {

        redisLog(REDIS_NOTICE,
            "Successful partial resynchronization with master.");
        sdsfree(reply);
        replicationResurrectCachedMaster(fd);
        return PSYNC_CONTINUE;
    }


    if (strncmp(reply,"-ERR",4)) {

        redisLog(REDIS_WARNING,
            "Unexpected reply to PSYNC from master: %s", reply);
    } else {
        redisLog(REDIS_NOTICE,
            "Master does not support PSYNC or is in "
            "error state (reply: %s)", reply);
    }
    sdsfree(reply);
    replicationDiscardCachedMaster();
    return PSYNC_NOT_SUPPORTED;
}
