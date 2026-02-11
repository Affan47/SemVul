VersionAuditFile()

{ char *sp;

if (sp = GetMacroValue(CONTEXTID,"cfinputs_version"))
   {
   AUDITPTR->version = strdup(sp);
   }
else
   {
   Verbose("Cfengine input file had no explicit version string\n");
   }
}
