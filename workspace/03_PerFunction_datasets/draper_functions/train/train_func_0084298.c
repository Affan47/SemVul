__ecereNameSpace__ecere__com__Byte_OnCompare(struct __ecereNameSpace__ecere__com__Class * _class, unsigned char * data1, unsigned char * data2)
{
int result = 0;

if(*data1 > *data2)
result = 1;
else if(*data1 < *data2)
result = -1;
return result;
}
