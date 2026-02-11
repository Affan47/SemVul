__ecereNameSpace__ecere__com__SearchNameSpace(struct __ecereNameSpace__ecere__com__NameSpace * nameSpace, char * name, void * listOffset)
{
int start = 0, c;
char ch;
int level = 0;

for(c = 0; (ch = name[c]); c++)
{
if(ch == '<')
level++;
if(ch == '>')
level--;
if(level == 0 && (ch == '.' || (ch == ':' && name[c + 1] == ':')))
{
struct __ecereNameSpace__ecere__com__NameSpace * newSpace;
char * spaceName = __ecereNameSpace__ecere__com___malloc(c - start + 1);

memcpy(spaceName, name + start, c - start);
spaceName[c - start] = '\0';
newSpace = (struct __ecereNameSpace__ecere__com__NameSpace *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&nameSpace->nameSpaces, spaceName);
__ecereNameSpace__ecere__com___free(spaceName);
if(!newSpace)
return (((void *)0));
nameSpace = newSpace;
if(level == 0 && ch == ':')
c++;
start = c + 1;
}
}
if(c - start)
{
return __ecereNameSpace__ecere__com__ScanNameSpace(nameSpace, name + start, listOffset);
}
return (((void *)0));
}
