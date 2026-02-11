__ecereMethod___ecereNameSpace__ecere__sys__File_Tell(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);

return __ecerePointer___ecereNameSpace__ecere__sys__File->input ? ftell(__ecerePointer___ecereNameSpace__ecere__sys__File->input) : ftell(__ecerePointer___ecereNameSpace__ecere__sys__File->output);
}
