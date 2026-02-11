__ecereMethod___ecereNameSpace__ecere__sys__TempFile_Getc(struct __ecereNameSpace__ecere__com__Instance * this, char * ch)
{
struct __ecereNameSpace__ecere__sys__TempFile * __ecerePointer___ecereNameSpace__ecere__sys__TempFile = (struct __ecereNameSpace__ecere__sys__TempFile *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__TempFile->offset) : 0);
int read = ((int (*)(struct __ecereNameSpace__ecere__com__Instance *, void *  buffer, unsigned int size, unsigned int count))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__TempFile->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Read])(this, ch, 1, 1);

return !__ecerePointer___ecereNameSpace__ecere__sys__TempFile->eof && read != 0;
}
