__ecereNameSpace__ecere__sys__FileGetSize(char * fileName, unsigned int * size)
{
unsigned int result = 0x0;

if(size)
{
*size = 0;
if(fileName)
{
result = FILE_FileGetSize(fileName, size);
}
}
return result;
}
