main(int    argc,
     char **argv)
{
l_int32       i, success, display;
FILE         *fp;
L_REGPARAMS  *rp;

    if (regTestSetup(argc, argv, &fp, &display, &success, &rp))
        return 1;

    for (i = 0; i < 4; i++) {

        TestImage(image[i], i, rp);
    }

    regTestCleanup(argc, argv, fp, success, rp);
    return 0;
}
