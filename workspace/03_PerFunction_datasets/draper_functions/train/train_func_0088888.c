ODM_RAInfo_Init_all(struct odm_dm_struct *dm_odm)
{
	u8 macid = 0;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD, ("=====>\n"));
	dm_odm->CurrminRptTime = 0;

	for (macid = 0; macid < ODM_ASSOCIATE_ENTRY_NUM; macid++)
		ODM_RAInfo_Init(dm_odm, macid);

	return 0;
}
