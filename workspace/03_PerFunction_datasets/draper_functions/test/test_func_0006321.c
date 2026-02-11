do_artinfo(struct reader *r)
{
    struct rs_cmd *cmd = r->buf;
    struct rs_artinfo *reply;
    char *group = (char *)(r->buf) + sizeof(struct rs_cmd);
    TOKEN token;

    debug("OVDB: rs: do_artinfo: '%s' %d", group, cmd->artlo);
    if(ovdb_getartinfo(group, cmd->artlo, &token)) {
    	reply = xmalloc(sizeof(struct rs_artinfo));
	reply->status = CMD_ARTINFO;
	reply->token = token;
	r->buflen = sizeof(struct rs_artinfo);
    } else {
    	reply = xmalloc(sizeof(struct rs_artinfo));
	reply->status = CMD_ARTINFO | RPLY_ERROR;
	r->buflen = sizeof(struct rs_artinfo);
    }
    free(r->buf);
    r->buf = reply;
    r->bufpos = 0;
    r->mode = MODE_WRITE;
}
