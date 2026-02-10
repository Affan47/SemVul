ParseArrayValue(struct __ecereNameSpace__ecere__com__Instance * array, char * equal)
{
char * start, * comma;
char * string;

string = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(equal);
start = string;
while(start)
{
comma = strstr(start, ",");
if(comma)
comma[0] = '\0';
((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = array;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(array, (uint64)(__ecereFunction___ecereNameSpace__ecere__sys__CopyString(start)));
if(comma)
comma++;
if(comma)
comma++;
start = comma;
}
(__ecereNameSpace__ecere__com__eSystem_Delete(string), string = 0);
}
