TransStreamOut(Pool *p, Handle *h, Transform T)
{
    FILE *outf;

    if ((outf = PoolOutputFile(p)) == NULL) {
	return false;
    }

    fprintf(outf, "transform {\n");
    PoolIncLevel(p, 1);
    if (PoolStreamOutHandle(p, h, true)) {
	fputtransform(outf, 1, &T[0][0], 0);
    }
    PoolIncLevel(p, -1);
    PoolFPrint(p, outf, "}\n");

    return !ferror(outf);
}
