dump_ads (const char *source_file,
	  void (*collect_all_refs)(const char *),
	  int (*cpp_check)(tree, cpp_operation))
{
  char *ads_name;
  char *pkg_name;
  char *s;
  FILE *f;

  pkg_name = get_ada_package (source_file);


  ads_name = xstrdup (pkg_name);

  for (s = ads_name; *s; s++)
    if (*s == '.')
      *s = '-';
    else
      *s = TOLOWER (*s);

  ads_name = reconcat (ads_name, ads_name, ".ads", NULL);


  f = fopen (ads_name, "w");
  if (f)
    {
      pretty_printer pp;

      pp_construct (&pp, NULL, 0);
      pp_needs_newline (&pp) = true;
      pp.buffer->stream = f;


      dump_ada_macros (&pp, source_file);


      reset_ada_withs ();

      (*collect_all_refs) (source_file);


      dump_ada_nodes (&pp, source_file, cpp_check);


      fprintf (f, "pragma Ada_2005;\npragma Style_Checks (Off);\n\n");


      dump_ada_withs (f);

      fprintf (f, "\npackage %s is\n\n", pkg_name);
      pp_write_text_to_stream (&pp);

      fprintf (f, "end %s;\n", pkg_name);
      fclose (f);
    }

  free (ads_name);
  free (pkg_name);
}
