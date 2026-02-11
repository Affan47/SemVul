load(const char *file)
{
	FILE *fp;

	fp=fopen(file, "r");
	if(!fp)
		return false;

	while(Specs.size())
	{
		delete Specs[0];
		Specs.erase(Specs.begin());
	}

	char buf[1024];

	while(fgets(buf, 1024, fp))
	{
		int byte, mask, code;

		if(sscanf(buf, "%d %d %d", &byte, &mask, &code) == 3)
		{
			BitfieldSpec *s=new BitfieldSpec;
			s->byte=byte;
			s->mask=(unsigned char)(mask & 0xff);
			s->code=code;

			Specs.push_back(s);
		}
	}
	fclose(fp);

	return true;
}
