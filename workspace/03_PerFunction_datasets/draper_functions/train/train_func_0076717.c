main(int    argc,
             char **argv)
{
char         buf[256], rootname[256];
char        *dir, *pattern, *psdir, *imagedir;
char        *fname, *tail, *filename;
l_int32      i, n, ret;
SARRAY      *sa, *saps;
static char  mainName[] = "concatpdf";

    if (argc != 2 && argc != 3)
        return ERROR_INT("Syntax: concatpdf dir [pattern]", mainName, 1);
    dir = argv[1];
    pattern = (argc == 3) ? argv[2] : NULL;


    sa = getSortedPathnamesInDirectory(dir, pattern, 0, 0);
    sarrayWriteStream(stderr, sa);
    n = sarrayGetCount(sa);

#if 1

    psdir = genPathname("/tmp/ps", NULL);
    lept_rmdir("ps");
    lept_mkdir("ps");
    saps = sarrayCreate(n);
    for (i = 0; i < n; i++) {
        fname = sarrayGetString(sa, i, L_NOCOPY);
        splitPathAtDirectory(fname, NULL, &tail);
        splitPathAtExtension(tail, &filename, NULL);
        snprintf(buf, sizeof(buf), "acroread -toPostScript -annotsOff %s %s",
                 fname, psdir);
        fprintf(stderr, "%s\n", buf);
        ret = system(buf);
        snprintf(buf, sizeof(buf), "%s/%s.ps", psdir, filename);
        sarrayAddString(saps, buf, L_COPY);
        lept_free(tail);
        lept_free(filename);
    }
    sarrayDestroy(&sa);
#endif

#if 1

    imagedir = genPathname("/tmp/image", NULL);
    lept_rmdir("image");
    lept_mkdir("image");
    sarrayWriteStream(stderr, saps);
    n = sarrayGetCount(saps);
    for (i = 0; i < n; i++) {
        fname = sarrayGetString(saps, i, L_NOCOPY);
        snprintf(rootname, sizeof(rootname), "%s/r%d", imagedir, i);
        snprintf(buf, sizeof(buf), "ps2png-gray %s %s", fname, rootname);
        fprintf(stderr, "%s\n", buf);
        ret = system(buf);
    }
#endif

#if 1

    convertFilesToPdf(imagedir, "png", RESOLUTION, 1.0, L_FLATE_ENCODE,
                      0, "", "/tmp/output.pdf");
#endif

    return 0;
}
