__ecereMethod___ecereNameSpace__eda__DirFilesDataSourceDriver_UpdateDatabaseList(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__DirFilesDataSourceDriver * __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver = (struct __ecereNameSpace__eda__DirFilesDataSourceDriver *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__DirFilesDataSourceDriver->offset) : 0);
struct __ecereNameSpace__ecere__sys__FileListing listing =
{
__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->path, __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databaseFileExt
};

((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databases;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])(__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databases);
while(__ecereMethod___ecereNameSpace__ecere__sys__FileListing_Find(&listing))
{
if(((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char *  fullPath))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__eda__DirFilesDataSourceDriver->_vTbl;
})[__ecereVMethodID___ecereNameSpace__eda__DirFilesDataSourceDriver_IsDatabaseFile])(this, __ecereProp___ecereNameSpace__ecere__sys__FileListing_Get_path(&listing)))
{
char * ext = __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databaseFileExt;
char * fileName = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(__ecereProp___ecereNameSpace__ecere__sys__FileListing_Get_name(&listing));

if(ext && *ext)
{
char fileExt[17];

__ecereFunction___ecereNameSpace__ecere__sys__GetExtension(fileName, fileExt);
if(!strcmp(fileExt, ext))
__ecereFunction___ecereNameSpace__ecere__sys__StripExtension(fileName);
}
((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databases;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(__ecerePointer___ecereNameSpace__eda__DirFilesDataSourceDriver->databases, (uint64)(fileName));
}
}
}
