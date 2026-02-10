dump_rt(struct lib_context *lc, struct asr_raidtable *rt)
{
	unsigned i;

	DP("ridcode:\t\t\t0x%X", rt, rt->ridcode);
	DP("rversion:\t\t%d", rt, rt->rversion);
	DP("max configs:\t\t%d", rt, rt->maxelm);
	DP("configs:\t\t\t%d", rt, rt->elmcnt);
	DP("config sz:\t\t%d", rt, rt->elmsize);
	DP("checksum:\t\t\t0x%X", rt, rt->rchksum);
	DP("raid flags:\t\t0x%X", rt, rt->raidFlags);
	DP("timestamp:\t\t0x%X", rt, rt->timestamp);
	P("irocFlags:\t\t%X%s", rt, rt->irocFlags, rt->irocFlags,
	  rt->irocFlags & ASR_IF_BOOTABLE ? " (bootable)" : "");
	DP("dirt, rty:\t\t%d", rt, rt->dirty);
	DP("action prio:\t\t%d", rt, rt->actionPriority);
	DP("spareid:\t\t\t%d", rt, rt->spareid);
	DP("sparedrivemagic:\t\t0x%X", rt, rt->sparedrivemagic);
	DP("raidmagic:\t\t0x%X", rt, rt->raidmagic);
	DP("verifydate:\t\t0x%X", rt, rt->verifyDate);
	DP("recreatedate:\t\t0x%X", rt, rt->recreateDate);

	log_print(lc, "\nRAID config table:");
	for (i = 0; i < rt->elmcnt; i++)
		dump_cl(lc, &rt->ent[i]);
}
