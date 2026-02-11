gf_clock_attach(GF_List *clocks, GF_Scene *scene, u16 clockID, u16 ES_ID, s32 hasOCR)
{
	Bool check_dep;
	GF_Clock *tmp = gf_clock_find(clocks, clockID, ES_ID);

	check_dep = (scene->root_od->net_service && scene->root_od->net_service->Clocks==clocks) ? 1 : 0;

	if (!tmp && check_dep) tmp = CK_LookForClockDep(scene, clockID);
	if (!tmp) {
		tmp = NewClock(scene->root_od->term);
		tmp->clockID = clockID;
		gf_list_add(clocks, tmp);
	} else {
		if (tmp->clockID == ES_ID) tmp->clockID = clockID;

		if (check_dep && (tmp->clockID != ES_ID)) CK_ResolveClockDep(clocks, scene, tmp, ES_ID);
	}
	if (hasOCR >= 0) tmp->use_ocr = hasOCR;
	return tmp;
}
