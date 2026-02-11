next_dentry (void)
{
	ldtentry_t *de;
	s8 *stbl;

	if (jfs.dttype == DTTYPE_INLINE) {
		if (jfs.sindex < jfs.slastindex) {
			return (ldtentry_t *)&dtroot->slot[(int)dtroot->header.stbl[jfs.sindex++]];
		}
	} else {
		de = (ldtentry_t *)dtpage->slot;
		stbl = (s8 *)&de[(int)dtpage->header.stblindex];
		if (jfs.sindex < jfs.slastindex) {
			return &de[(int)stbl[jfs.sindex++]];
		} else if (dtpage->header.next) {
			devread (dtpage->header.next << jfs.bdlog, 0,
				 sizeof(dtpage_t), (char *)dtpage);
			jfs.slastindex = dtpage->header.nextindex;
			jfs.sindex = 1;
			return &de[(int)((s8 *)&de[(int)dtpage->header.stblindex])[0]];
		}
	}

	return (jfs.de_index < 2) ? &de_always[jfs.de_index++] : NULL;
}
