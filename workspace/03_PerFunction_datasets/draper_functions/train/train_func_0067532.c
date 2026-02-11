__ecereNameSpace__ecere__sys__GetLastDirectory(char * string, char * output)
{
int c;
int len = string ? strlen(string) : 0;

for(c = len - 2; c >= 0; c--)
if(string[c] == '/' || string[c] == '\\' || string[c] == ':' || string[c] == '>')
break;
c++;
if(c >= 0)
strcpy(output, string + c);
else
output[0] = '\0';
len = strlen(output);
if(len > 1 && (output[len - 1] == '\\' || output[len - 1] == '/'))
output[len - 1] = '\0';
return output;
}
