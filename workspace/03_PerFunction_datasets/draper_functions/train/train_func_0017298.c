name_or_number(const char *string, const id_name_map map[]) {
   int result;
   char *endptr;

   result=strtoul(string, &endptr, 0);
   if (endptr != string)
      return result;

   result=name_to_id(string, map);
   if (result == -1)
      err_msg("Invalid value: %s", string);

   return result;
}
