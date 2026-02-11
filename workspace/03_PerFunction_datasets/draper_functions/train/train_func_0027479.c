__ecereMethod___ecereNameSpace__ecere__sys__EARFileSystem_Exists(char * archive, char * fileName)
{
unsigned int result = 0;
struct __ecereNameSpace__ecere__sys__EARHeader header;
struct __ecereNameSpace__ecere__com__Instance * f = __ecereNameSpace__ecere__sys__EAROpenArchive(archive, &header);

if(f)
{
struct __ecereNameSpace__ecere__sys__EAREntry entry =
{
0, 0, 0, 0, 0, 0, 0, 0
};

result = (unsigned int)__ecereNameSpace__ecere__sys__EARGetEntry(f, &entry, fileName, (((void *)0)));
(__ecereNameSpace__ecere__com__eInstance_DecRef(f), f = 0);
}
return result;
}
