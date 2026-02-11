aof_create_new_segment(void) {
    if(server.aof_state == REDIS_AOF_OFF) {
        return REDIS_ERR;
    }
    if(server.aof_fd != -1) {

        server.aof_buf = sdscat(server.aof_buf, "*1\r\n$11\r\nLOADNEXTAOF\r\n");

        flushAppendOnlyFile(1);
        aof_fsync(server.aof_fd);
        close(server.aof_fd);
        server.aof_selected_db = -1;
    }

    server.aof_current_segment++;
    server.aof_fd = aof_open_current_segment(1);

    if(server.aof_fd == -1) {
        server.aof_fd = -1;
        server.aof_state = REDIS_AOF_OFF;
        redisLog(REDIS_WARNING, "Failed to create a new AOF segment! AOF disabled.");
        return REDIS_ERR;
    }
    sds filename = aof_get_current_segment_filename();
    redisLog(REDIS_NOTICE, "Created a new AOF segment: %s", filename);
    sdsfree(filename);
    return REDIS_OK;
}
