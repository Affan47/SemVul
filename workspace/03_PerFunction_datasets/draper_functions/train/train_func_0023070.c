_push_to_hashtbl(pid_t ppid, pid_t pid,
			     int is_usercmd, char *cmd, xppid_t **hashtbl)
{
	int idx;
	xppid_t *ppids, *newppid;
	xpid_t *newpid;

	idx = GET_HASH_IDX(ppid);
	ppids = hashtbl[idx];
	while (ppids) {
		if (ppids->ppid == ppid) {
			newpid = _alloc_pid(pid, is_usercmd, cmd, ppids->list);
			ppids->list = newpid;
			return;
		}
		ppids = ppids->next;
	}
	newppid = _alloc_ppid(ppid, pid, is_usercmd, cmd, hashtbl[idx]);
	hashtbl[idx] = newppid;
}
