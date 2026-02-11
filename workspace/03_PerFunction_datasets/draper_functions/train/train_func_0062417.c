hid_set_value(const char *varname, const char *val)
{
	int retcode, i, replen;
	mge_info_item_t *shut_info_p;
   HIDData_t hData;

	upsdebugx(2, "============== entering hid_set_value(%s, %s) ==============", varname, val);


	shut_info_p = shut_find_info(varname);

	if (shut_info_p == NULL || shut_info_p->type == NULL ||
		!(shut_info_p->flags & SHUT_FLAG_OK))
	{
		upsdebugx(2, "hid_ups_set: info element unavailable %s", varname);
		return STAT_SET_UNKNOWN;
	}


	if (!shut_info_p->flags & ST_FLAG_RW) {
		upsdebugx(2, "hid_ups_set: not writable %s", varname);
		return STAT_SET_UNKNOWN;
	}


	if (shut_info_p->shut_flags & SHUT_FLAG_ABSENT) {
		upsdebugx(2, "hid_ups_set: setting server side variable %s", varname);
		dstate_setinfo(shut_info_p->type, "%s", val);
		return STAT_SET_HANDLED;
	} else {

		if (shut_info_p->item_path == NULL) {
			upsdebugx(2, "hid_ups_set: ID Path is NULL for %s", varname);
			return STAT_SET_UNKNOWN;
		}
	}


	hData.Type = ITEM_FEATURE;
	hData.ReportID = 0;

	if((retcode = lookup_path(shut_info_p->item_path, &hData)) > 0) {
		upsdebugx(3, "Path depth = %i\n", retcode);

		for (i = 0; i<retcode; i++)
			upsdebugx(4, "%i: Usage(%08x)\n", i, hData.Path.Node[i]);

		hData.Path.Size = retcode;


		if (FindObject(pDesc,&hData) == 1) {
			replen = shut_get_report(hData.ReportID, raw_buf, MAX_REPORT_SIZE);

			GetValue((const u_char *) raw_buf, &hData, &hValue);


			if (hData.Attribute != ATTR_DATA_CST) {

				hValue = atol(val);
				SetValue(&hData, raw_buf, hValue);
				shut_set_report(hData.ReportID, raw_buf, replen);


				return STAT_SET_HANDLED;
			}
			else
				upsdebugx(3, "Object is constant");
		}
		else
			upsdebugx(3, "Can't find object");
	}
	else
		upsdebugx(3, "Can't lookup object's path");

	return STAT_SET_UNKNOWN;
}
