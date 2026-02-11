CommandImportParty(char *sz)
{
    FILE *gamf, *matf, *pf;
    char *tmpfile;
    int rc;

    sz = NextToken(&sz);

    if (!sz || !*sz) {
        outputl(_("You must specify a PartyGammon file to import (see `help " "import party')."));
        return;
    }

    if ((gamf = g_fopen(sz, "r")) == 0) {
        outputerr(sz);
        return;
    }

    tmpfile = g_strdup_printf("%s.mat", sz);
    if (g_file_test(tmpfile, G_FILE_TEST_EXISTS)) {
        outputerrf("%s is in the way. Cannot import %s\n", tmpfile, sz);
        g_free(tmpfile);
        fclose(gamf);
        return;
    }

    if ((matf = g_fopen(tmpfile, "w")) == 0) {
        outputerr(tmpfile);
        g_free(tmpfile);
        fclose(gamf);
        return;
    }

    if (ConvertPartyGammonFileToMat(gamf, matf)) {
        if ((pf = g_fopen(tmpfile, "r")) != 0) {
            rc = ImportMat(pf, tmpfile);
            fclose(pf);
            if (!rc) {
                setDefaultFileName(tmpfile);
                if (fGotoFirstGame)
                    CommandFirstGame(NULL);
            }
        } else
            outputerr(tmpfile);
    } else
        outputerrf("Failed to convert gam to mat\n");
    g_unlink(tmpfile);
    g_free(tmpfile);
}
