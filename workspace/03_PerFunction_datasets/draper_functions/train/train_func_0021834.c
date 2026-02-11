__ecereMethod___ecereNameSpace__eda__DirFilesDataSourceDriver_MakeDatabasePath(struct __ecereNameSpace__ecere__com__Instance * this, const char * name)
{
struct __ecereNameSpace__eda__DirFilesDataSourceDriver * __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver = (struct __ecereNameSpace__eda__DirFilesDataSourceDriver *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__DirFilesDataSourceDriver->offset) : 0);

if(name)
{
char dbPath[797];
char * ext = __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databaseFileExt;

strcpy(dbPath, __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->path ? __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->path : "");
if(ext && *ext)
{
char * fileName = __ecereNameSpace__ecere__com__eSystem_New(sizeof(char) * (strlen(name) + strlen(ext) + 8));
char nameExt[17];

__ecereFunction___ecereNameSpace__ecere__sys__GetExtension(name, nameExt);
strcpy(fileName, name);
if(!nameExt[0] || strcmp(nameExt, ext))
{
strcat(fileName, ".");
strcat(fileName, ext);
}
__ecereFunction___ecereNameSpace__ecere__sys__PathCat(dbPath, fileName);
(__ecereNameSpace__ecere__com__eSystem_Delete(fileName), fileName = 0);
}
else
__ecereFunction___ecereNameSpace__ecere__sys__PathCat(dbPath, name);
return __ecereFunction___ecereNameSpace__ecere__sys__CopyString(dbPath);
}
return (((void *)0));
}
