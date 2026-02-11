__ecereNameSpace__ecere__com__Byte_OnGetDataFromString(struct __ecereNameSpace__ecere__com__Class * _class, unsigned char * data, char * string)
{
char * end;
unsigned char result = (unsigned char)strtoul(string, &end, 0);

if(end > string)
{
*data = result;
return 0x1;
}
return 0x0;
}
