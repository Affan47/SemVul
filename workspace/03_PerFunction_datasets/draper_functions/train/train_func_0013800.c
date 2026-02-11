__ecereMethod___ecereNameSpace__ecere__sys__File_GetLine(struct __ecereNameSpace__ecere__com__Instance * this, char * s, int max)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);
int c = 0;
unsigned int result = 0x1;

s[c] = (char)0;
if(((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Eof])(this))
{
result = 0x0;
}
else
{
while(c < max - 1)
{
char ch = (char)0;

if(!((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char *  ch))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Getc])(this, &ch))
{
result = 0x0;
break;
}
if(ch == '\n')
break;
if(ch != '\r')
s[c++] = ch;
}
}
s[c] = (char)0;
return result || c > 1;
}
