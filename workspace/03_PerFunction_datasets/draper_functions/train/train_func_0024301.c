importer_generate_matrix (gint bracket, gint rows, gint cols) {
    gint i = 0, j = 0;
    static gchar result[BUFSIZ * 2] = { 0 };
    gchar tmp[BUFSIZ / 8];


    result[0] = 0;

    strncat (result, "$\\begin{", BUFSIZ * 2 -strlen (result) -1);
    strncat (result, bracket_type[bracket], BUFSIZ * 2 -strlen (result) -1);
    strncat (result, "}", BUFSIZ * 2 - strlen (result) -1);

    for (i = 0; i < rows; ++i) {
        strncat (result, "\n\t", BUFSIZ * 2 -strlen (result) -1);
        for (j = 0; j < cols; ++j) {
            snprintf (tmp, BUFSIZ/8, "%d%d", i + 1, j + 1);
            strncat (result, tmp, BUFSIZ * 2 -strlen (result) -1);
            if (j != cols -1)
                strncat (result, " & ", BUFSIZ * 2 -strlen (result) -1);
            else
                strncat (result, "\\\\", BUFSIZ * 2 -strlen (result) -1);
        }
    }
    strncat (result, "\n\\end{", BUFSIZ * 2 -strlen (result) -1);
    strncat (result, bracket_type[bracket], BUFSIZ * 2 -strlen (result) -1);
    strncat (result, "}$\n", BUFSIZ * 2 -strlen (result) -1);
    return result;
}
