c_common_finish (void)
{
  FILE *deps_stream = NULL;

  if (cpp_opts->deps.style != DEPS_NONE)
    {


      if (!deps_file)
	deps_stream = out_stream;
      else
	{
	  deps_stream = fopen (deps_file, deps_append ? "a": "w");
	  if (!deps_stream)
	    fatal_error ("opening dependency file %s: %m", deps_file);
	}
    }


  errorcount += cpp_finish (parse_in, deps_stream);

  if (deps_stream && deps_stream != out_stream
      && (ferror (deps_stream) || fclose (deps_stream)))
    fatal_error ("closing dependency file %s: %m", deps_file);

  if (out_stream && (ferror (out_stream) || fclose (out_stream)))
    fatal_error ("when writing output to %s: %m", out_fname);
}
