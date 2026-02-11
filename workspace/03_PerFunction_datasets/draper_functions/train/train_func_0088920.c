swap_phontab (const char *infile, const char *outfile)
{
    FILE *in, *out;
    char buf_8[8];
    int i, n_phoneme_tables;

    in = fopen (infile, "rb");
    if (in == NULL) {
        fprintf (stderr, "Unable to read from file %s\n", infile);
        exit (1);
    }

    out = fopen (outfile, "wb");
    if (out == NULL) {
        fprintf (stderr, "Unable to open file %s for writing\n", outfile);
        exit (1);
    }

    xread = fread (buf_8, 4, 1, in);
    fwrite (buf_8, 4, 1, out);
    n_phoneme_tables = buf_8[0];

    for (i = 0; i < n_phoneme_tables; i++) {
        int n_phonemes, j;
        char tab_name[N_PHONEME_TAB_NAME];

        xread = fread (buf_8, 8, 1, in);
        fwrite (buf_8, 8, 1, out);

        n_phonemes = buf_8[0];

        xread = fread (tab_name, N_PHONEME_TAB_NAME, 1, in);
        fwrite (tab_name, N_PHONEME_TAB_NAME, 1, out);

        for (j = 0; j < n_phonemes; j++) {
            PHONEME_TAB table;

            xread = fread (&table, sizeof (PHONEME_TAB), 1, in);

            table.mnemonic = SWAP_UINT (table.mnemonic);
            table.phflags = SWAP_UINT (table.phflags);
            table.program = SWAP_USHORT (table.program);

            fwrite (&table, sizeof (PHONEME_TAB), 1, out);
        }
    }

    fclose (in);
    fclose (out);
}
