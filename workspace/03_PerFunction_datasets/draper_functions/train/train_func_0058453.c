msgfmt_frob_new_message (default_catalog_reader_ty *that, message_ty *mp,
                         const lex_pos_ty *msgid_pos,
                         const lex_pos_ty *msgstr_pos)
{
  msgfmt_catalog_reader_ty *this = (msgfmt_catalog_reader_ty *) that;

  if (!mp->obsolete)
    {


      if ((!include_untranslated && mp->msgstr[0] == '\0')
          || (!include_fuzzies && mp->is_fuzzy && !is_header (mp)))
        {
          if (check_compatibility)
            {
              error_with_progname = false;
              error_at_line (0, 0, mp->pos.file_name, mp->pos.line_number,
                             (mp->msgstr[0] == '\0'
                              ? _("empty 'msgstr' entry ignored")
                              : _("fuzzy 'msgstr' entry ignored")));
              error_with_progname = true;
            }


          if (mp->msgstr[0] == '\0')
            ++msgs_untranslated;
          else
            ++msgs_fuzzy;

          mp->obsolete = true;
        }
      else
        {

          if (is_header (mp))
            {
              this->has_header_entry = true;
              if (!mp->is_fuzzy)
                this->has_nonfuzzy_header_entry = true;
            }
          else


            if (mp->is_fuzzy)
              ++msgs_fuzzy;
            else
              ++msgs_translated;
        }
    }
}
