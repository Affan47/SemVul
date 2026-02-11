c_parse_error (const char *gmsgid, enum cpp_ttype token_type,
	       tree value, unsigned char token_flags)
{
#define catenate_messages(M1, M2) catenate_strings ((M1), (M2), sizeof (M2))

  char *message = NULL;

  if (token_type == CPP_EOF)
    message = catenate_messages (gmsgid, " at end of input");
  else if (token_type == CPP_CHAR
	   || token_type == CPP_WCHAR
	   || token_type == CPP_CHAR16
	   || token_type == CPP_CHAR32)
    {
      unsigned int val = TREE_INT_CST_LOW (value);
      const char *prefix;

      switch (token_type)
	{
	default:
	  prefix = "";
	  break;
	case CPP_WCHAR:
	  prefix = "L";
	  break;
	case CPP_CHAR16:
	  prefix = "u";
	  break;
	case CPP_CHAR32:
	  prefix = "U";
	  break;
        }

      if (val <= UCHAR_MAX && ISGRAPH (val))
	message = catenate_messages (gmsgid, " before %s'%c'");
      else
	message = catenate_messages (gmsgid, " before %s'\\x%x'");

      error (message, prefix, val);
      free (message);
      message = NULL;
    }
  else if (token_type == CPP_STRING
	   || token_type == CPP_WSTRING
	   || token_type == CPP_STRING16
	   || token_type == CPP_STRING32
	   || token_type == CPP_UTF8STRING)
    message = catenate_messages (gmsgid, " before string constant");
  else if (token_type == CPP_NUMBER)
    message = catenate_messages (gmsgid, " before numeric constant");
  else if (token_type == CPP_NAME)
    {
      message = catenate_messages (gmsgid, " before %qE");
      error (message, value);
      free (message);
      message = NULL;
    }
  else if (token_type == CPP_PRAGMA)
    message = catenate_messages (gmsgid, " before %<#pragma%>");
  else if (token_type == CPP_PRAGMA_EOL)
    message = catenate_messages (gmsgid, " before end of line");
  else if (token_type == CPP_DECLTYPE)
    message = catenate_messages (gmsgid, " before %<decltype%>");
  else if (token_type < N_TTYPES)
    {
      message = catenate_messages (gmsgid, " before %qs token");
      error (message, cpp_type2name (token_type, token_flags));
      free (message);
      message = NULL;
    }
  else
    error (gmsgid);

  if (message)
    {
      error (message);
      free (message);
    }
#undef catenate_messages
}
