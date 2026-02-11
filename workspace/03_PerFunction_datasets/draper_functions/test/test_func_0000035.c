process_panel_info (xmlNodePtr cur, DATASET *dset)
{
    xmlChar *tmp;
    double sd0 = 0.0;
    int pd = 0;

    tmp = xmlGetProp(cur, (XUC) "group-names");
    if (tmp != NULL) {
	dset->pangrps = (char *) tmp;
    }

    tmp = xmlGetProp(cur, (XUC) "time-frequency");
    if (tmp != NULL) {
	pd = atoi((const char *) tmp);
	free(tmp);
    }

    tmp = xmlGetProp(cur, (XUC) "time-start");
    if (tmp != NULL) {
	sd0 = atof((const char *) tmp);
	free(tmp);
    }

    if (pd > 0 && sd0 > 0.0) {
	dset->panel_pd = pd;
	dset->panel_sd0 = sd0;
    }

    return 0;
}
