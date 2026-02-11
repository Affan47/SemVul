__ecereMethod___ecereNameSpace__ecere__sys__EARArchive_FileExists(struct __ecereNameSpace__ecere__com__Instance * this, char * fileName)
{
struct __ecereNameSpace__ecere__sys__EARArchive * __ecerePointer___ecereNameSpace__ecere__sys__EARArchive = (struct __ecereNameSpace__ecere__sys__EARArchive *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__EARArchive->offset) : 0);
unsigned int result;
struct __ecereNameSpace__ecere__sys__EAREntry entry =
{
0, 0, 0, 0, 0, 0, 0, 0
};

((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int pos, int mode))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__sys__EARArchive->f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Seek])(__ecerePointer___ecereNameSpace__ecere__sys__EARArchive->f, __ecerePointer___ecereNameSpace__ecere__sys__EARArchive->archiveStart + sizeof(struct __ecereNameSpace__ecere__sys__EARHeader), 0);
result = __ecereNameSpace__ecere__sys__EARGetEntry(__ecerePointer___ecereNameSpace__ecere__sys__EARArchive->f, &entry, fileName, (((void *)0)));
return result;
}
