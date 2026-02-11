FullClassNameCat(char * output, char * className, unsigned int includeTemplateParams)
{
int c;
char ch;
int len;

for(c = 0; (ch = className[c]) && ch != '<'; c++)
{
if(ch == ':')
{
strcat(output, "__ecereNameSpace__");
break;
}
}
len = strlen(output);
for(c = 0; (ch = className[c]); c++)
{
if(ch == ':')
output[len++] = '_';
else if(ch == ' ')
output[len++] = '_';
else if(ch == '*')
{
output[len++] = '_';
output[len++] = 'P';
output[len++] = 'T';
output[len++] = 'R';
output[len++] = '_';
}
else if(ch == '=')
{
output[len++] = '_';
output[len++] = 'E';
output[len++] = 'Q';
output[len++] = 'U';
output[len++] = '_';
}
else if(ch == '<')
{
if(!includeTemplateParams)
break;
output[len++] = '_';
output[len++] = 'T';
output[len++] = 'P';
output[len++] = 'L';
output[len++] = '_';
}
else if(ch == '>')
{
output[len++] = '_';
}
else if(ch == ',')
{
output[len++] = '__';
}
else
output[len++] = ch;
}
output[len++] = (char)0;
}
