__ecereMethod___ecereNameSpace__ecere__sys__ArchiveDir_Add(struct __ecereNameSpace__ecere__com__Instance * this, char * name, char * path, int addMode, int compression, int * ratio, unsigned int * newPosition)
{
unsigned int result = 0x0;
struct __ecereNameSpace__ecere__com__Instance * file = __ecereNameSpace__ecere__sys__FileOpen(path, 1);

if(file)
{
struct __ecereNameSpace__ecere__sys__FileStats stats;

__ecereNameSpace__ecere__sys__FileGetStats(path, &stats);
result = ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char *  name, struct __ecereNameSpace__ecere__com__Instance * input, struct __ecereNameSpace__ecere__sys__FileStats * stats, int addMode, int compression, int *  ratio, unsigned int *  newPosition))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__ArchiveDir->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__ArchiveDir_AddFromFile])(this, name, file, &stats, addMode, compression, ratio, newPosition);
(__ecereNameSpace__ecere__com__eInstance_DecRef(file), file = 0);
}
return result;
}
