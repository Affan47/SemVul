__ecereMethod___ecereNameSpace__ecere__sys__BufferedFile_Lock(struct __ecereNameSpace__ecere__com__Instance * this, int type, uint64 start, uint64 length, unsigned int wait)
{
struct __ecereNameSpace__ecere__sys__BufferedFile * __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile = (struct __ecereNameSpace__ecere__sys__BufferedFile *)(this ? (((char *)this) + 40) : 0);

return ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int type, uint64 start, uint64 length, unsigned int wait))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Lock])(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle, type, start, length, wait);
}
