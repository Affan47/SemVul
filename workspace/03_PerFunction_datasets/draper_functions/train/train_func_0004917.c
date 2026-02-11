test_start_page (CRDocHandler * a_handler,
                 CRString * a_name,
                 CRString * a_pseudo_page,
                 CRParsingLocation *a_location)
{
        guchar *name = NULL,
                *pseudo_page = NULL;

        g_return_if_fail (a_handler);

        fprintf (stdout, "***************\n");
        fprintf (stdout, "start_page\n");

        if (a_name) {
                name = cr_string_dup2 (a_name) ;
        }
        if (a_pseudo_page) {
                pseudo_page = cr_string_dup2 (a_pseudo_page);
        }
        if (name) {
                fprintf (stdout, "%s", name);
        }
        if (pseudo_page) {
                fprintf (stdout, ": %s\n", pseudo_page);
        }
        fprintf (stdout, "***************\n\n");
        if (name) {
                g_free (name);
                name = NULL;
        }
        if (pseudo_page) {
                g_free (pseudo_page);
                pseudo_page = NULL;
        }
}
