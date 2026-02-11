pmsg_clone_extend(pmsg_t *mb, pmsg_free_t free_cb, void *arg)
{
	pmsg_ext_t *nmb;

	pmsg_check_consistency(mb);

	WALLOC(nmb);
	nmb->pmsg = *mb;
	nmb->pmsg.magic = PMSG_EXT_MAGIC;

	pdata_addref(nmb->pmsg.m_data);

	nmb->pmsg.m_flags |= PMSG_PF_EXT;
	nmb->pmsg.m_refcnt = 1;
	nmb->m_free = free_cb;
	nmb->m_arg = arg;

	return cast_to_pmsg(nmb);
}
