HandleEdit(char *file,char *edit,char *string)

{
if (! IsInstallable(CLASSBUFF))
   {
   InitializeAction();
   Debug1("Not installing Edit no match\n");
   return;
   }

if (string == NULL)
   {
   Debug1("Handling Edit of %s, action [%s] with no data if (%s)\n",file,edit,CLASSBUFF);
   }
else
   {
   Debug1("Handling Edit of %s, action [%s] with data <%s> if (%s)\n",file,edit,string,CLASSBUFF);
   }

if (EditFileExists(file))
   {
   AddEditAction(file,edit,string);
   }
else
   {
   InstallEditFile(file,edit,string);
   }
}
