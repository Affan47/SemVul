agent_devicestate(const char *data)
{
	struct agent_pvt *p;
	const char *device = data;
	int res = AST_DEVICE_INVALID;

	if (device[0] == '@' || device[0] == ':') {

		return AST_DEVICE_INVALID;
	}


	AST_LIST_LOCK(&agents);
	AST_LIST_TRAVERSE(&agents, p, list) {
		ast_mutex_lock(&p->lock);
		if (!p->pending && !strcmp(device, p->agent)) {
			if (p->owner) {
				res = AST_DEVICE_BUSY;
			} else if (p->chan) {
				if (p->lastdisc.tv_sec || p->deferlogoff) {

					res = AST_DEVICE_INUSE;
				} else {
					res = AST_DEVICE_NOT_INUSE;
				}
			} else {
				res = AST_DEVICE_UNAVAILABLE;
			}
			ast_mutex_unlock(&p->lock);
			break;
		}
		ast_mutex_unlock(&p->lock);
	}
	AST_LIST_UNLOCK(&agents);
	return res;
}
