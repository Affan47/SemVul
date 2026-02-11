__ecereMethod___ecereNameSpace__ecere__sys__File_Lock(struct __ecereNameSpace__ecere__com__Instance * this, int type, uint64 start, uint64 length, unsigned int wait)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);

return FILE_Lock(__ecerePointer___ecereNameSpace__ecere__sys__File->input, __ecerePointer___ecereNameSpace__ecere__sys__File->output, type, start, length, wait);
}
