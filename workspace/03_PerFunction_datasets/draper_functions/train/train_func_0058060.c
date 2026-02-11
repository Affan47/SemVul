main(int argc, char *argv[])
{
    char *usage = "usage: %s file.geo file.tiff\n"
        "geo\tfile containing projection (eg. from listgeo)\n"
        "tiff\tTIFF file into which the projection is written\n";
    char *prog;
    char *geofile;
    char *tiffile;
    int rc;

    prog = argv[0];
    geofile = argv[1];
    tiffile = argv[2];

    if (!geofile || !tiffile)
    {
        fprintf(stderr, usage, prog);
        exit(1);
    }

    rc = InstallGeoTIFF(geofile, tiffile);
    if (rc)
    {
        fprintf(stderr, "%s: error %d applying projection from %s into TIFF %s\n", prog, rc, geofile, tiffile);
        exit(2);
    }

    return(0);
}
