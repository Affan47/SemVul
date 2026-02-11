ST_loadUnloadGraphics(load_callback_t callback)
{

    int		i;
    int		j;
    int		facenum;

    char	namebuf[9];


    for (i=0;i<10;i++)
    {
	DEH_snprintf(namebuf, 9, "STTNUM%d", i);
        callback(namebuf, &tallnum[i]);

	DEH_snprintf(namebuf, 9, "STYSNUM%d", i);
        callback(namebuf, &shortnum[i]);
    }


    callback(DEH_String("STTPRCNT"), &tallpercent);


    for (i=0;i<NUMCARDS;i++)
    {
	DEH_snprintf(namebuf, 9, "STKEYS%d", i);
        callback(namebuf, &keys[i]);
    }


    callback(DEH_String("STARMS"), &armsbg);


    for (i=0; i<6; i++)
    {
	DEH_snprintf(namebuf, 9, "STGNUM%d", i+2);


        callback(namebuf, &arms[i][0]);


	arms[i][1] = shortnum[i+2];
    }


    DEH_snprintf(namebuf, 9, "STFB%d", consoleplayer);
    callback(namebuf, &faceback);


    callback(DEH_String("STBAR"), &sbar);


    facenum = 0;
    for (i=0; i<ST_NUMPAINFACES; i++)
    {
	for (j=0; j<ST_NUMSTRAIGHTFACES; j++)
	{
	    DEH_snprintf(namebuf, 9, "STFST%d%d", i, j);
            callback(namebuf, &faces[facenum]);
            ++facenum;
	}
	DEH_snprintf(namebuf, 9, "STFTR%d0", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
	DEH_snprintf(namebuf, 9, "STFTL%d0", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
	DEH_snprintf(namebuf, 9, "STFOUCH%d", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
	DEH_snprintf(namebuf, 9, "STFEVL%d", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
	DEH_snprintf(namebuf, 9, "STFKILL%d", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
    }

    callback(DEH_String("STFGOD0"), &faces[facenum]);
    ++facenum;
    callback(DEH_String("STFDEAD0"), &faces[facenum]);
    ++facenum;
}
