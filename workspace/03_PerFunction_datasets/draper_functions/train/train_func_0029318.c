generateXPM(stateenum newstate, stateenum oldstate)
{
   char* address = &xpm_generic_var[xpm_generic_first_color][xpm_generic_column];
   switch (newstate) {
   case error:
      strcpy(address, "ff0000");
      break;
   case idle:
      strcpy(address, "ffffff");
      break;
   case running:
      strcpy(address, "00ff00");
      break;
   case warn:
      strcpy(address, "ffff00");
      break;
   }

   address = &xpm_generic_var[xpm_generic_second_color][xpm_generic_column];
   switch (oldstate) {
   case error:
      strcpy(address, "ff0000");
      break;
   case idle:
      strcpy(address, "ffffff");
      break;
   case running:
      strcpy(address, "00ff00");
      break;
   case warn:
      strcpy(address, "ffff00");
      break;
   }

   return (const char**)xpm_generic_var;
}
