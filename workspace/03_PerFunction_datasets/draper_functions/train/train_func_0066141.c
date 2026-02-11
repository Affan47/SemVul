__ecereMethod___ecereNameSpace__ecere__sys__File_Unlock(struct __ecereNameSpace__ecere__com__Instance * this, uint64 start, uint64 length, unsigned int wait)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);

return ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int type, uint64 start, uint64 length, unsigned int wait))this->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Lock])(this, 0, start, length, wait);
}
