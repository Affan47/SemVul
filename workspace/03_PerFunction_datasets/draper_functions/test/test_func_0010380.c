read_chasenrc(void)
{
    FILE *fp;
    char *rcpath;

    rcpath = cha_get_rcpath();

    fp = cha_fopen(rcpath, "r", 1);
    cha_read_rcfile_fp(fp);
    fclose(fp);


    if (!Cha_undef_info[0].hinsi)
	cha_exit(1, "%s: UNKNOWN_POS/michigo-hinsi is not specified",
		 cha_get_rcpath());

    if (!Da_ndicfile)
	cha_exit(1, "%s: dictionary is not specified",
		 cha_get_rcpath());
}
