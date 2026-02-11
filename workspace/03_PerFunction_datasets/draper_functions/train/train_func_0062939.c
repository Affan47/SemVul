MSNametoOutlet(struct pluginDevice* ms, const char * name)
{
	char	NameMapping[128];
	int	sockno;
	char	sockname[32];
	int times = 0;
	int ret = -1;


	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");


	EXPECT(ms->rdfd, Prompt, 5);


	SEND(ms->wrfd, "1\r");


	EXPECT(ms->rdfd, Separator, 5);
	EXPECT(ms->rdfd, CRNL, 5);
	EXPECT(ms->rdfd, CRNL, 5);


	do {
		times++;
		NameMapping[0] = EOS;
		SNARF(ms->rdfd, NameMapping, 5);
		if (sscanf(NameMapping
		,	"%d- %23c",&sockno, sockname) == 2) {

			char *	last = sockname+23;
			*last = EOS;
			--last;


			for(; last > sockname; --last) {
				if (*last == ' ') {
					*last = EOS;
				}else{
					break;
				}
			}
			if (strcasecmp(name, sockname) == 0) {
				ret = sockno;
			}
		}
	} while (strlen(NameMapping) > 2 && times < 8);


	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	EXPECT(ms->rdfd, Prompt, 5);
	SEND(ms->wrfd, "\033");
	return(ret);
}
