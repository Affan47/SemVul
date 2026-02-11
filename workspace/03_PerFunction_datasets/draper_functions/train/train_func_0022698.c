main(int argc, char **argv)
{
    FILE *dskfile;
    char count[2], volname[21];
    int i, result, fd;
    int pifd = a2open(argc > 1 ? argv[1] : "127.0.0.1");
    if (pifd < 0)
    {
	perror("Unable to connect to Apple II Pi");
	exit(EXIT_FAILURE);
    }
    a2write(pifd, ORG, sizeof(online),  online);
    a2call(pifd, ORG, &result);
    a2read(pifd, DATA_BUFFER, 16, volname);
    volname[(volname[0] & 0x0F) + 1] = '\0';
    printf("Volume name:%s\n", volname + 1);
    strcat(volname + 1, ".PO");
    a2write(pifd, ORG, sizeof(readblk), readblk);
    for (i = 0; i < 280; i++)
    {
	printf("Reading block #%d\r", i);
	fflush(stdout);
	count[0] = i;
	count[1] = i >> 8;
	a2write(pifd, BLOCK_NUM, 2, count);
	a2call(pifd, ORG, &result);
	a2read(pifd, DATA_BUFFER, 512, dsk[i]);
    }
    a2close(pifd);
    if ((dskfile = fopen(volname + 1, "wb")))
    {
	fwrite(dsk, 1, 280*512, dskfile);
	fclose(dskfile);
    }
    return EXIT_SUCCESS;
}
