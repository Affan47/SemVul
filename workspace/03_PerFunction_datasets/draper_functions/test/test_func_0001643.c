cr_statement_dump_ruleset (CRStatement const * a_this, FILE * a_fp, glong a_indent)
{
        guchar *str = NULL;

        g_return_if_fail (a_fp && a_this);
        str = cr_statement_ruleset_to_string (a_this, a_indent);
        if (str) {
                fprintf (a_fp, "%s", str);
                g_free (str);
                str = NULL;
        }
}
