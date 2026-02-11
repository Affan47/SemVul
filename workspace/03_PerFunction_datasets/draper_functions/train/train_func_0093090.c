is_startstring(char *string)
{
   if (*string == '\"' || *string == '\'')
      return TRUE;

   if (*string == '!')
     {
	string++;
	if (*string == '\"' || *string == '\'')
	   return TRUE;
	if (*string == sc_ctrlchar)
	  {
	     string++;
	     if (*string == '\"' || *string == '\'')
		return TRUE;
	  }
     }
   else if (*string == sc_ctrlchar)
     {
	string++;
	if (*string == '\"' || *string == '\'')
	   return TRUE;
	if (*string == '!')
	  {
	     string++;
	     if (*string == '\"' || *string == '\'')
		return TRUE;
	  }
     }

   return FALSE;
}
