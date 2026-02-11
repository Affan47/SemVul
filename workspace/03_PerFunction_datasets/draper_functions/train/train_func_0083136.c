print_line (pfile, map, line, special_flags)
     cpp_reader *pfile;
     const struct line_map *map;
     unsigned int line;
     const char *special_flags;
{

  if (pfile->print.printed)
    putc ('\n', pfile->print.outf);
  pfile->print.printed = 0;

  pfile->print.line = line;
  if (! CPP_OPTION (pfile, no_line_commands))
    {
      size_t to_file_len = strlen (map->to_file);
      unsigned char *to_file_quoted = alloca (to_file_len * 4 + 1);
      unsigned char *p;


      p = cpp_quote_string (to_file_quoted,
			    (unsigned char *)map->to_file, to_file_len);
      *p = '\0';
      fprintf (pfile->print.outf, "# %u \"%s\"%s",
	       SOURCE_LINE (map, pfile->print.line),
	       to_file_quoted, special_flags);

      if (map->sysp == 2)
	fputs (" 3 4", pfile->print.outf);
      else if (map->sysp == 1)
	fputs (" 3", pfile->print.outf);

      putc ('\n', pfile->print.outf);
    }
}
