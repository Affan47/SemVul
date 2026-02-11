afs_deliver_vl_get_entry_by_xxx(struct afs_call *call,
					   struct sk_buff *skb, bool last)
{
	struct afs_cache_vlocation *entry;
	__be32 *bp;
	u32 tmp;
	int loop;

	_enter(",,%u", last);

	afs_transfer_reply(call, skb);
	if (!last)
		return 0;

	if (call->reply_size != call->reply_max)
		return -EBADMSG;


	entry = call->reply;
	bp = call->buffer;

	for (loop = 0; loop < 64; loop++)
		entry->name[loop] = ntohl(*bp++);
	entry->name[loop] = 0;
	bp++;

	bp++;
	entry->nservers = ntohl(*bp++);

	for (loop = 0; loop < 8; loop++)
		entry->servers[loop].s_addr = *bp++;

	bp += 8;

	for (loop = 0; loop < 8; loop++) {
		tmp = ntohl(*bp++);
		entry->srvtmask[loop] = 0;
		if (tmp & AFS_VLSF_RWVOL)
			entry->srvtmask[loop] |= AFS_VOL_VTM_RW;
		if (tmp & AFS_VLSF_ROVOL)
			entry->srvtmask[loop] |= AFS_VOL_VTM_RO;
		if (tmp & AFS_VLSF_BACKVOL)
			entry->srvtmask[loop] |= AFS_VOL_VTM_BAK;
	}

	entry->vid[0] = ntohl(*bp++);
	entry->vid[1] = ntohl(*bp++);
	entry->vid[2] = ntohl(*bp++);

	bp++;

	tmp = ntohl(*bp++);
	entry->vidmask = 0;
	if (tmp & AFS_VLF_RWEXISTS)
		entry->vidmask |= AFS_VOL_VTM_RW;
	if (tmp & AFS_VLF_ROEXISTS)
		entry->vidmask |= AFS_VOL_VTM_RO;
	if (tmp & AFS_VLF_BACKEXISTS)
		entry->vidmask |= AFS_VOL_VTM_BAK;
	if (!entry->vidmask)
		return -EBADMSG;

	_leave(" = 0 [done]");
	return 0;
}
