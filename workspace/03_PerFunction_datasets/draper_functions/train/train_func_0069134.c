AgentDiagnostic(char *file)

{
if (VERBOSE || DEBUG)
   {
   FREPORT_TXT = stdout;
   FREPORT_HTML = fopen(NULLFILE,"w");
   FKNOW = fopen(NULLFILE,"w");
   }
else
   {
   FREPORT_TXT= fopen(NULLFILE,"w");
   FREPORT_HTML= fopen(NULLFILE,"w");
   FKNOW = fopen(NULLFILE,"w");
   }


printf("----------------------------------------------------------\n");
printf("Cfengine 3 - Performing level 2 self-diagnostic (dialogue)\n");
printf("----------------------------------------------------------\n\n");
TestVariableScan();
TestExpandPromise();
TestExpandVariables();

CheckInstalledLibraries();

#ifdef BUILD_TESTSUITE

if(file != NULL)
{

printf("----------------------------------------------------------\n");
printf("Cfengine 3 - Performing test suite                        \n");
printf("----------------------------------------------------------\n\n");
InitializeGA(0,NULL);
 TestSuite(file);
}

#else
printf("!! Extensive self-diagnostic capabilities not built in\n");
#endif

}
