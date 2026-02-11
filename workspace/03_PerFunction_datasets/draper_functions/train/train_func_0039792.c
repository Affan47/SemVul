__ecereNameSpace__ecere__sys__GetExtension(char * string, char * output)
{
int __simpleStruct0;
int c;
int len = strlen(string);
int limit = (__simpleStruct0 = len - (17), (0 > __simpleStruct0) ? 0 : __simpleStruct0);

output[0] = '\0';
for(c = len; c >= limit; c--)
{
char ch = string[c];

if(ch == '.')
{
strcpy(output, string + c + 1);
break;
}
else if(ch == '/' || ch == '\\')
break;
}
return output;
}
