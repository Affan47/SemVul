fobject_ref(vmon_t *vmon, vmon_fobject_t *fobject, vmon_proc_fd_t *fd_ref)
{
	fobject->refcnt++;

	if(fd_ref) {
		list_add_tail(&fd_ref->ref_fds, &fobject->ref_fds);
	}
}
