send_command(struct cardstate *cs, const char *cmd,
			 struct at_state_t *at_state)
{
	int cid = at_state->cid;
	struct cmdbuf_t *cb;
	size_t buflen;

	buflen = strlen(cmd) + 12;
	cb = kmalloc(sizeof(struct cmdbuf_t) + buflen, GFP_ATOMIC);
	if (!cb) {
		dev_err(cs->dev, "%s: out of memory\n", __func__);
		return;
	}
	if (cid > 0 && cid <= 65535)
		cb->len = snprintf(cb->buf, buflen,
				   cs->dle ? "\020(AT%d%s\020)" : "AT%d%s",
				   cid, cmd);
	else
		cb->len = snprintf(cb->buf, buflen,
				   cs->dle ? "\020(AT%s\020)" : "AT%s",
				   cmd);
	cb->offset = 0;
	cb->next = NULL;
	cb->wake_tasklet = NULL;
	cs->ops->write_cmd(cs, cb);
}
