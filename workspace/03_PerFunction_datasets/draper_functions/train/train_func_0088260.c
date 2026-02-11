CommandRelationalSelect(char *sz)
{
    unsigned int i, j;
    RowSet *rs;

    if (!sz || !*sz) {
        outputl(_("You must specify a sql query to run."));
        return;
    }

    rs = RunQuery(sz);
    if (!rs)
        return;

    if (rs->rows == 0) {
        outputl(_("No rows found.\n"));
        return;
    }
#if USE_GTK
    if (fX)
        GtkShowQuery(rs);
    else
#endif
        for (i = 0; i < rs->rows; i++) {
            if (i == 1) {
                char *line, *p;
                unsigned int k;
                int totalwidth = 0;
                for (k = 0; k < rs->cols; k++) {
                    totalwidth += rs->widths[k] + 1;
                    if (k != 0)
                        totalwidth += 2;
                }
                line = malloc(totalwidth + 1);
                memset(line, '-', totalwidth);
                p = line;
                for (k = 0; k < rs->cols - 1; k++) {
                    p += rs->widths[k];
                    p[1] = '|';
                    p += 3;
                }
                line[totalwidth] = '\0';
                outputl(line);
                free(line);
            }

            for (j = 0; j < rs->cols; j++) {
                if (j > 0)
                    output(" | ");

                outputf("%*s", (int) rs->widths[j], rs->data[i][j]);
            }
            outputl("");
        }
    FreeRowset(rs);
}
