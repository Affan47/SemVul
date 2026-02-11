afslog(int argc, char **argv)
{
    int ret;
    if(argc > 2) {
	printf("usage: %s [cell]\n", argv[0]);
	code = -1;
	return;
    }
    if(argc == 2)
	ret = command("SITE AFSLOG %s", argv[1]);
    else
	ret = command("SITE AFSLOG");
    code = (ret == COMPLETE);
}
