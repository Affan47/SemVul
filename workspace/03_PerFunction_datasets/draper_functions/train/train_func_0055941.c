__ecereMethod___ecereNameSpace__ecere__sys__File_Getc(struct __ecereNameSpace__ecere__com__Instance * this, char * ch)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);
int ich = fgetc(__ecerePointer___ecereNameSpace__ecere__sys__File->input);

if(ich != (-1))
{
if(ch)
*ch = (char)ich;
return 0x1;
}
return 0x0;
}
