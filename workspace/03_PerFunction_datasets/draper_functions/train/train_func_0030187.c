compat_input(struct dlm_write_request *kb,
			 struct dlm_write_request32 *kb32,
			 int namelen)
{
	kb->version[0] = kb32->version[0];
	kb->version[1] = kb32->version[1];
	kb->version[2] = kb32->version[2];

	kb->cmd = kb32->cmd;
	kb->is64bit = kb32->is64bit;
	if (kb->cmd == DLM_USER_CREATE_LOCKSPACE ||
	    kb->cmd == DLM_USER_REMOVE_LOCKSPACE) {
		kb->i.lspace.flags = kb32->i.lspace.flags;
		kb->i.lspace.minor = kb32->i.lspace.minor;
		memcpy(kb->i.lspace.name, kb32->i.lspace.name, namelen);
	} else if (kb->cmd == DLM_USER_PURGE) {
		kb->i.purge.nodeid = kb32->i.purge.nodeid;
		kb->i.purge.pid = kb32->i.purge.pid;
	} else {
		kb->i.lock.mode = kb32->i.lock.mode;
		kb->i.lock.namelen = kb32->i.lock.namelen;
		kb->i.lock.flags = kb32->i.lock.flags;
		kb->i.lock.lkid = kb32->i.lock.lkid;
		kb->i.lock.parent = kb32->i.lock.parent;
		kb->i.lock.xid = kb32->i.lock.xid;
		kb->i.lock.timeout = kb32->i.lock.timeout;
		kb->i.lock.castparam = (void *)(long)kb32->i.lock.castparam;
		kb->i.lock.castaddr = (void *)(long)kb32->i.lock.castaddr;
		kb->i.lock.bastparam = (void *)(long)kb32->i.lock.bastparam;
		kb->i.lock.bastaddr = (void *)(long)kb32->i.lock.bastaddr;
		kb->i.lock.lksb = (void *)(long)kb32->i.lock.lksb;
		memcpy(kb->i.lock.lvb, kb32->i.lock.lvb, DLM_USER_LVB_LEN);
		memcpy(kb->i.lock.name, kb32->i.lock.name, namelen);
	}
}
