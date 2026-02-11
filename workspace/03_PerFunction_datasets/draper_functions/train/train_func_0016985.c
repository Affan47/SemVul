perl_ban_fill_hash(HV *hv, BAN_REC *ban)
{
	hv_store(hv, "ban", 3, new_pv(ban->ban), 0);
	hv_store(hv, "setby", 5, new_pv(ban->setby), 0);
	hv_store(hv, "time", 4, newSViv(ban->time), 0);
}
