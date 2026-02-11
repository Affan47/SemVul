main(int argc,char *argv[])

{
int ret = 0;

CheckOpts(argc,argv);
GenericInitialize(argc,argv,"agent");
ThisAgentInit();
KeepPromises();
NoteClassUsage(VHEAP);
#ifdef HAVE_NOVA
Nova_NoteVarUsageDB();
#endif
PurgeLocks();

if(BOOTSTRAP && !VerifyBootstrap())
   {
   ret = 1;
   }

GenericDeInitialize();

return ret;
}
