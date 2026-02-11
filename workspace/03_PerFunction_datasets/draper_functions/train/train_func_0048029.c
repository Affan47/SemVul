seq_set_string(InputSeq* a, const char *buf)
{
	char *lbuf;
	char *arg = NULL;
	int j;
	struct ik *pik;
	int found;


	lbuf = malloc (strlen(buf)+1);


	strcpy (lbuf, buf);

	for(j=0;j<SEQ_MAX;++j)
		(*a)[j] = CODE_NONE;

	arg = strtok(lbuf, " \t\r\n");
	j = 0;
	while( arg != NULL )
	{
		found = 0;

		pik = input_keywords;

		while (!found && pik->name && pik->name[0] != 0)
		{
			if (strcmp(pik->name,arg) == 0)
			{

				if (pik->type == IKT_STD)
				{
					(*a)[j] = pik->val;
					j++;
					found = 1;
				}
			}
			pik++;
		}

		pik = osd_input_keywords;

		if (pik)
		{
			while (!found && pik->name && pik->name[0] != 0)
			{
				if (strcmp(pik->name,arg) == 0)
				{
					switch (pik->type)
					{
						case IKT_STD:
							(*a)[j] = pik->val;
							j++;
							found = 1;
						break;

						case IKT_OSD_KEY:
							(*a)[j] = keyoscode_to_code(pik->val);
							j++;
							found = 1;
						break;

						case IKT_OSD_JOY:
							(*a)[j] = joyoscode_to_code(pik->val);
							j++;
							found = 1;
						break;
					}
				}
				pik++;
			}
		}

		arg = strtok(NULL, " \t\r\n");
	}
	free (lbuf);
}
