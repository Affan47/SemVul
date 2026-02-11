extract (FILE *fp,
         const char *real_filename, const char *logical_filename,
         catalog_input_format_ty input_syntax,
         msgdomain_list_ty *mdlp)
{
  default_catalog_reader_ty *pop;

  header_charset = NULL;

  pop = default_catalog_reader_alloc (&extract_methods);
  pop->handle_comments = true;
  pop->handle_filepos_comments = (line_comment != 0);
  pop->allow_domain_directives = false;
  pop->allow_duplicates = false;
  pop->allow_duplicates_if_same_msgstr = true;
  pop->file_name = real_filename;
  pop->mdlp = NULL;
  pop->mlp = mdlp->item[0]->messages;
  catalog_reader_parse ((abstract_catalog_reader_ty *) pop, fp, real_filename,
                        logical_filename, input_syntax);
  catalog_reader_free ((abstract_catalog_reader_ty *) pop);

  if (header_charset != NULL)
    {
      if (!xgettext_omit_header)
        {

          message_ty *mp =
            message_list_search (mdlp->item[0]->messages, NULL, "");

          if (mp != NULL && !mp->obsolete)
            {
              const char *header = mp->msgstr;

              if (header != NULL)
                {
                  const char *charsetstr = strstr (header, "charset=");

                  if (charsetstr != NULL)
                    {
                      size_t len, len1, len2, len3;
                      char *new_header;

                      charsetstr += strlen ("charset=");
                      len = strcspn (charsetstr, " \t\n");

                      len1 = charsetstr - header;
                      len2 = strlen (header_charset);
                      len3 = (header + strlen (header)) - (charsetstr + len);
                      new_header = XNMALLOC (len1 + len2 + len3 + 1, char);
                      memcpy (new_header, header, len1);
                      memcpy (new_header + len1, header_charset, len2);
                      memcpy (new_header + len1 + len2, charsetstr + len, len3 + 1);
                      mp->msgstr = new_header;
                      mp->msgstr_len = len1 + len2 + len3 + 1;
                    }
                }
            }
        }

      free (header_charset);
    }
}
