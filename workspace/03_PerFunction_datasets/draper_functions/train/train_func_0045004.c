parse_long_option(int argc, const char** argv, bool equals_only,
		  const char** arg, int* i)
{
  const char* const this_argv = argv[*i];

  const char* equals = strchr(this_argv, '=');
  const char* option_start = this_argv + strspn(this_argv, "-");
  std::string option(option_start,
		     equals ? equals - option_start : strlen(option_start));

  gold::options::Option_map::iterator it
      = gold::options::long_options->find(option);
  if (it == gold::options::long_options->end())
    return NULL;

  gold::options::One_option* retval = it->second;


  if (this_argv[0] != '-')
    {
      if (retval->dashes != gold::options::DASH_Z)
	return NULL;
    }
  else if (this_argv[1] != '-')
    {
      if (retval->dashes != gold::options::ONE_DASH
	  && retval->dashes != gold::options::EXACTLY_ONE_DASH
	  && retval->dashes != gold::options::TWO_DASHES)
	return NULL;
    }
  else
    {
      if (retval->dashes != gold::options::TWO_DASHES
	  && retval->dashes != gold::options::EXACTLY_TWO_DASHES
	  && retval->dashes != gold::options::ONE_DASH)
	return NULL;
    }


  ++(*i);


  if (!retval->takes_argument())
    {
      if (equals)
	usage(_("unexpected argument"), this_argv);
      else
	*arg = NULL;
    }
  else
    {
      if (equals)
	*arg = equals + 1;
      else if (retval->takes_optional_argument())
	*arg = retval->default_value;
      else if (*i < argc && !equals_only)
	*arg = argv[(*i)++];
      else
	usage(_("missing argument"), this_argv);
    }

  return retval;
}
