__dlm_lockres_grab_inflight_ref(struct dlm_ctxt *dlm,
				   struct dlm_lock_resource *res)
{
	res->inflight_locks++;

	mlog(0, "%s: res %.*s, inflight++: now %u, %ps()\n", dlm->name,
	     res->lockname.len, res->lockname.name, res->inflight_locks,
	     __builtin_return_address(0));
}
