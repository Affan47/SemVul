tag_to_type (const char *tag, SCM port)
{
#if SCM_ENABLE_DEPRECATED
  {


    const char *instead;
    switch (tag[0])
      {
      case 'u':
	instead = "u32";
	break;
      case 'e':
	instead = "s32";
	break;
      case 's':
	instead = "f32";
	break;
      case 'i':
	instead = "f64";
	break;
      case 'y':
	instead = "s8";
	break;
      case 'h':
	instead = "s16";
	break;
      case 'l':
	instead = "s64";
	break;
      case 'c':
	instead = "c64";
	break;
      default:
	instead = NULL;
	break;
      }

    if (instead && tag[1] == '\0')
      {
	scm_c_issue_deprecation_warning_fmt
	  ("The tag '%c' is deprecated for uniform vectors. "
	   "Use '%s' instead.", tag[0], instead);
	return scm_from_locale_symbol (instead);
      }
  }
#endif

  if (*tag == '\0')
    return SCM_BOOL_T;
  else
    return scm_from_locale_symbol (tag);
}
