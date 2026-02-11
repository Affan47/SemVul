setrule(const char *s)
{
   const char* colonptr = strchr(s,':');
   string rule_name(s);
   if(colonptr)
      rule_name.assign(s,colonptr);


   if (stricmp(rule_name.c_str(), RULE_STRINGS[JvN29]) == 0 ||
        stricmp(rule_name.c_str(), "JvN-29") == 0)
      current_rule = JvN29;
   else if (stricmp(rule_name.c_str(), RULE_STRINGS[Nobili32]) == 0 ||
        stricmp(rule_name.c_str(), "JvN-32") == 0)
      current_rule = Nobili32;
   else if (stricmp(rule_name.c_str(), RULE_STRINGS[Hutton32]) == 0 ||
        stricmp(rule_name.c_str(), "modJvN-32") == 0)
      current_rule = Hutton32;
   else {
      return "This algorithm only supports these rules: JvN29, Nobili32, Hutton32.";
   }


   if (colonptr) {
      const char* err = setgridsize(colonptr);
      if (err) return err;
   } else {

      gridwd = 0;
      gridht = 0;
   }

   maxCellStates = N_STATES[current_rule];
   ghashbase::setrule(RULE_STRINGS[current_rule]);
   return NULL;
}
