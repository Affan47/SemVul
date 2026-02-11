dlm_drop_lockres_ref(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	struct dlm_deref_lockres deref;
	int ret = 0, r;
	const char *lockname;
	unsigned int namelen;

	lockname = res->lockname.name;
	namelen = res->lockname.len;
	BUG_ON(namelen > O2NM_MAX_NAME_LEN);

	memset(&deref, 0, sizeof(deref));
	deref.node_idx = dlm->node_num;
	deref.namelen = namelen;
	memcpy(deref.name, lockname, namelen);

	ret = o2net_send_message(DLM_DEREF_LOCKRES_MSG, dlm->key,
				 &deref, sizeof(deref), res->owner, &r);
	if (ret < 0)
		mlog(ML_ERROR, "%s: res %.*s, error %d send DEREF to node %u\n",
		     dlm->name, namelen, lockname, ret, res->owner);
	else if (r < 0) {

		mlog(ML_ERROR, "%s: res %.*s, DEREF to node %u got %d\n",
		     dlm->name, namelen, lockname, res->owner, r);
		dlm_print_one_lock_resource(res);
		BUG();
	}
	return ret;
}
