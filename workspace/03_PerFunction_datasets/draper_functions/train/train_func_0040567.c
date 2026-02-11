do_include_common (cpp_reader *pfile, enum include_type type)
{
  const char *fname;
  int angle_brackets;

  fname = parse_include (pfile, &angle_brackets);
  if (!fname)
    return;

  if (!*fname)
  {
    cpp_error (pfile, CPP_DL_ERROR, "empty filename in #%s",
               pfile->directive->name);
    free ((void *) fname);
    return;
  }


  if (pfile->line_maps.depth >= CPP_STACK_MAX)
    cpp_error (pfile, CPP_DL_ERROR, "#include nested too deeply");
  else
    {

      skip_rest_of_line (pfile);

      if (pfile->cb.include)
	pfile->cb.include (pfile, pfile->directive_line,
			   pfile->directive->name, fname, angle_brackets);

      _cpp_stack_include (pfile, fname, angle_brackets, type);
    }

  free ((void *) fname);
}
