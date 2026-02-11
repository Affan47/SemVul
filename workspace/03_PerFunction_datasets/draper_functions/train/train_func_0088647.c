cpl_matrix_dump(const cpl_matrix *matrix, FILE *stream)
{
    cpl_size i, j, k;


    if (stream == NULL)
        stream = stdout;

    fprintf(stream, " ");

    if (matrix == NULL) {
        fprintf(stream, "NULL matrix\n\n");
        return;
    }

    fprintf(stream, "   ");
    for (j = 0; j < matrix->nc; j++)
        fprintf(stream, " %6" CPL_SIZE_FORMAT, j);

    fprintf(stream, "\n");

    for (k = 0, i = 0; i < matrix->nr; i++) {
        fprintf(stream, "  %" CPL_SIZE_FORMAT " ", i);
        for (j = 0; j < matrix->nc; j++, k++)
            fprintf(stream, " %6g", matrix->m[k]);

        fprintf(stream, "\n");
    }
    fprintf(stream, "\n");
}
