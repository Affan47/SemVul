init(const char *ConfigurationFile)
{
   int  error = 0;
   FILE *cnffp;

   if ((cnffp = fopen(ConfigurationFile, "r")) == NULL) {
      panic("Unable to open configuration file \"%s\"", ConfigurationFile);
      return(0);
   }

   initConfigStruct();

   if (!readConfigLines(cnffp)) {
      panic("Reading configuration file \"%s\" with errors", ConfigurationFile);
      error = 1;
   }

   fclose(cnffp);

   return(error ? 0 : 1);
}
