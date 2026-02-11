ImportMat(FILE * fp, char *szFilename)
{
    bgvariation bgv;

    if (!get_input_discard())
        return -1;
    FreeMatch();
    ClearMatch();

    for (bgv = VARIATION_STANDARD; bgv < NUM_VARIATIONS; bgv++) {
        gchar *str;
        if (ImportMatVariation(fp, szFilename, bgv, FALSE) == 0)
            return 0;
        str = g_strdup_printf(N_("Import as a %s match had errors. Try a different variation?"), aszVariations[bgv]);
        if (!GetInputYN(str)) {
            g_free(str);
            return 0;
        }
        g_free(str);


        if (fseek(fp, 0L, SEEK_SET) != 0)
            return -1;
        FreeMatch();
        ClearMatch();
    }

    return ImportMatVariation(fp, szFilename, VARIATION_STANDARD, -1);
}
