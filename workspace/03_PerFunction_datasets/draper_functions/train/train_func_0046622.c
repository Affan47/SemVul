bash_history_inhibit_expansion (string, i)
     char *string;
     int i;
{


  if (i > 0 && (string[i - 1] == '[') && member (']', string + i + 1))
    return (1);


  else if (i > 1 && string[i - 1] == '{' && string[i - 2] == '$' &&
	     member ('}', string + i + 1))
    return (1);
#if defined (EXTENDED_GLOB)
  else if (extended_glob && i > 1 && string[i+1] == '(' && member (')', string + i + 2))
    return (1);
#endif
  else
    return (0);
}
