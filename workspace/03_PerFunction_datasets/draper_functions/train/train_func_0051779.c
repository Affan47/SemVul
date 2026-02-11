asd_get_ddb(struct asd_ha_struct *asd_ha)
{
	int ddb, i;

	ddb = FIND_FREE_DDB(asd_ha);
	if (ddb >= asd_ha->hw_prof.max_ddbs) {
		ddb = -ENOMEM;
		goto out;
	}
	SET_DDB(ddb, asd_ha);

	for (i = 0; i < sizeof(struct asd_ddb_ssp_smp_target_port); i+= 4)
		asd_ddbsite_write_dword(asd_ha, ddb, i, 0);
out:
	return ddb;
}
