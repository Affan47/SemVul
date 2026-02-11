_osd_req_sec_params(struct osd_request *or)
{
	struct osd_cdb *ocdb = &or->cdb;

	if (osd_req_is_ver1(or))
		return (struct osd_security_parameters *)&ocdb->v1.sec_params;
	else
		return (struct osd_security_parameters *)&ocdb->v2.sec_params;
}
