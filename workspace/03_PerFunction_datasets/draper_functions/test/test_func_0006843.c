rc_config_free(rc_handle *rh)
{
	int i, j;
	SERVER *serv;

	if (rh->config_options == NULL)
		return;

	for (i = 0; i < NUM_OPTIONS; i++) {
		if (rh->config_options[i].val == NULL)
			continue;
		if (rh->config_options[i].type == OT_SRV) {
		        serv = (SERVER *)rh->config_options[i].val;
			for (j = 0; j < serv->max; j++){
				free(serv->name[j]);
				if(serv->secret[j]) free(serv->secret[j]);
			}
			free(serv);
		} else {
			free(rh->config_options[i].val);
		}
	}
	free(rh->config_options);
	rh->config_options = NULL;
}
