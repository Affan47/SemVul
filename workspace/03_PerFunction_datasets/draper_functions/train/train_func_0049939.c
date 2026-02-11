loadProfiles(AB_BANKING* ab)
{
	GWEN_DB_NODE *dbProfiles = AB_Banking_GetImExporterProfiles(ab,
								    this->name);
	GWEN_DB_NODE *n = GWEN_DB_GetFirstGroup(dbProfiles);
	while (n) {
		aqb_ieProfile *profile = new aqb_ieProfile(n);
		this->profiles->append(profile);

		n = GWEN_DB_GetNextGroup(n);
	}
	GWEN_DB_Group_free(dbProfiles);

	return this->profiles->size();
}
