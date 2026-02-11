start_element_gtkbuilder (struct element_state *p, const char *name,
                          const char **attributes)
{


  if (!p->extract_string)
    {
      bool has_translatable = false;
      const char *extracted_comment = NULL;
      const char *extracted_context = NULL;
      const char **attp = attributes;
      while (*attp != NULL)
        {
          if (strcmp (attp[0], "translatable") == 0)
            has_translatable = (strcmp (attp[1], "yes") == 0);
          else if (strcmp (attp[0], "comments") == 0)
            extracted_comment = attp[1];
          else if (strcmp (attp[0], "context") == 0)
            extracted_context = attp[1];
          attp += 2;
        }
      p->extract_string = has_translatable;
      p->extracted_comment =
        (has_translatable && extracted_comment != NULL
         ? xstrdup (extracted_comment)
         : NULL);
      p->extracted_context =
        (has_translatable && extracted_context != NULL
         ? xstrdup (extracted_context)
         : NULL);
   }
}
