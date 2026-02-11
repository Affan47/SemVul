LoadEnvelope(FILE *f, const char *fname)
{
	int displ;
	char buf[128];

	displ = ftell(f_phdata);

	fseek(f,12,SEEK_SET);
	if(fread(buf,128,1,f) == 0)
	{
		error("Failed to read envelope: %s",fname);
	}
	fwrite(buf,128,1,f_phdata);

	if(n_envelopes < N_ENVELOPES)
	{
		strncpy0(envelope_paths[n_envelopes],fname,sizeof(envelope_paths[0]));
		memcpy(envelope_dat[n_envelopes],buf,sizeof(envelope_dat[0]));
		n_envelopes++;
	}

	return(displ);
}
