SaveFCEUConfig(const char *filename, const CFGSTRUCT *cfgst)
{
	FILE *fp = fopen(filename,"wb");

	if(fp==NULL)
		return;
	fclose(fp);
	fp = fopen(filename,"wb");
	cfg_OldToNew(cfgst);
	cfg_Save(fp);
	fclose(fp);
}
