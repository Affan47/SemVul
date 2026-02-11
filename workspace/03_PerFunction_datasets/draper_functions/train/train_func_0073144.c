InstallEditFile(char *file,char *edit,char *data)

{ struct Edit *ptr;
  char ebuff[CF_EXPANDSIZE];

if (data == NULL)
   {
   Debug1("InstallEditFile(%s,%s,-) with classes %s\n",file,edit,CLASSBUFF);
   }
else
   {
   Debug1("InstallEditFile(%s,%s,%s) with classes %s\n",file,edit,data,CLASSBUFF);
   }

if (!IsInstallable(CLASSBUFF))
   {
   InitializeAction();
   Debug1("Not installing Edit no match\n");
   return;
   }

ExpandVarstring(file,ebuff,"");

if ((ptr = (struct Edit *)malloc(sizeof(struct Edit))) == NULL)
   {
   FatalError("Memory Allocation failed for InstallEditFile() #1");
   }

if ((ptr->fname = strdup(ebuff)) == NULL)
   {
   FatalError("Memory Allocation failed for InstallEditFile() #2");
   }

if (VEDITLISTTOP == NULL)
   {
   VEDITLIST = ptr;
   }
else
   {
   VEDITLISTTOP->next = ptr;
   }

if (strncmp(ebuff,"home",4) == 0 && strlen(ebuff) < 6)
   {
   yyerror("Can't edit home directories: missing a filename after home");
   }

if (strlen(LOCALREPOS) > 0)
   {
   ExpandVarstring(LOCALREPOS,ebuff,"");
   ptr->repository = strdup(ebuff);
   }
else
   {
   ptr->repository = NULL;
   }

if (PIFELAPSED != -1)
   {
   ptr->ifelapsed = PIFELAPSED;
   }
else
   {
   ptr->ifelapsed = VIFELAPSED;
   }

if (PEXPIREAFTER != -1)
   {
   ptr->expireafter = PEXPIREAFTER;
   }
else
   {
   ptr->expireafter = VEXPIREAFTER;
   }

ptr->audit = AUDITPTR;
ptr->logaudit = AUDITP;
ptr->lineno = LINENUMBER;
ptr->done = 'n';
ptr->split = CF_UNUSED_CHAR;
ptr->scope = strdup(CONTEXTID);
ptr->recurse = 0;
ptr->useshell = 'y';
ptr->binary = 'n';
ptr->next = NULL;
ptr->actions = NULL;
ptr->filters = NULL;
ptr->ignores = NULL;
ptr->umask = UMASK;
ptr->exclusions = NULL;
ptr->inclusions = NULL;
ptr->warn = 'n';
VEDITLISTTOP = ptr;
AddEditAction(file,edit,data);
}
