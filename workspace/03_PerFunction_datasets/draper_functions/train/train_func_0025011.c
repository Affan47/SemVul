charset (CRDocHandler *a_this,
         CRString *a_charset,
         CRParsingLocation *a_charset_sym_location)
{
        gchar *str = NULL ;

        g_return_if_fail (a_this && a_charset && a_charset_sym_location) ;

        str = (gchar*)cr_string_peek_raw_str (a_charset) ;
        if (str) {
                g_print ("\n\n@charset \"%s\";\n\n", str) ;
                str = NULL ;
        } else {
                return ;
        }
        g_print ("/********************************************\n") ;
        g_print (" * Parsing location information of the @charset rule\n") ;
        g_print (" ********************************************/\n") ;
        if (a_charset_sym_location) {
                str = cr_parsing_location_to_string (a_charset_sym_location, 0) ;
                if (str) {
                        g_print ("  /*@charset*/\n") ;
                        g_print ("  /*%s*/\n", str) ;
                        g_free (str) ;
                        str = NULL ;
                }
        }
        str = (gchar*) cr_string_peek_raw_str (a_charset) ;
        if (str) {
                g_print ("  /*%s*/\n", str) ;
                str = NULL ;
        }
        str = cr_parsing_location_to_string (&a_charset->location, 0) ;
        if (str) {
                g_print ("  /*%s*/\n\n", str) ;
                g_free (str) ;
                str = NULL ;
        }
}
