FilterExecMatch(char *filename,char *crit)


{ char ebuff[CF_EXPANDSIZE];

AddMacroValue(CONTEXTID,"this",filename);
ExpandVarstring(crit,ebuff,NULL);
DeleteMacro(CONTEXTID,"this");

Debug("Executing filter command [%s]\n",ebuff);

if (ShellCommandReturnsZero(ebuff,false))
   {
   return true;
   }
else
   {
   return false;
   }
}
