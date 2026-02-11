compute_file_name_parts (void)
{
  const char *base, *tab, *ext;


  if (spec_outfile)
    {
      file_name_split (spec_outfile, &base, &tab, &ext);
      dir_prefix = xstrndup (spec_outfile, base - spec_outfile);


      all_but_ext =
        xstrndup (spec_outfile,
                  (strlen (spec_outfile) - (ext ? strlen (ext) : 0)));


      all_but_tab_ext =
        xstrndup (spec_outfile,
                  (strlen (spec_outfile)
                   - (tab ? strlen (tab) : (ext ? strlen (ext) : 0))));

      if (ext)
        compute_exts_from_src (ext);
    }
  else
    {
      file_name_split (grammar_file, &base, &tab, &ext);

      if (spec_file_prefix)
        {

          dir_prefix =
            xstrndup (spec_file_prefix,
                      last_component (spec_file_prefix) - spec_file_prefix);
          all_but_tab_ext = xstrdup (spec_file_prefix);
        }
      else if (yacc_flag)
        {

          dir_prefix = xstrdup ("");
          all_but_tab_ext = xstrdup ("y");
        }
      else
        {


          dir_prefix = xstrdup ("");
          all_but_tab_ext =
            xstrndup (base, (strlen (base) - (ext ? strlen (ext) : 0)));
        }

      if (language->add_tab)
        all_but_ext = concat2 (all_but_tab_ext, TAB_EXT);
      else
        all_but_ext = xstrdup (all_but_tab_ext);


      if (ext && !yacc_flag)
        compute_exts_from_gf (ext);
    }
}
