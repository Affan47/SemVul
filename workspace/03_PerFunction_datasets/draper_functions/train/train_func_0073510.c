__ecereMethod_WatchMultiLineString_OnDisplay(struct __ecereNameSpace__ecere__com__Class * class, char * this, struct __ecereNameSpace__ecere__com__Instance * surface, int x, int y, int width, void * fieldData, int alignment, unsigned int displayFlags)
{
if((char *)this)
{
char ch;
char * string = this;
char actualString[8196];
int c, len = 0;

for(c = 0; (ch = string[c]) && len < sizeof actualString - 1; c++)
{
if(ch == '\t')
{
actualString[len++] = '\\';
actualString[len++] = 't';
}
else if(ch == '\r')
{
actualString[len++] = '\\';
actualString[len++] = 'r';
}
else if(ch == '\n')
{
actualString[len++] = '\\';
actualString[len++] = 'n';
}
else
actualString[len++] = ch;
}
actualString[len] = (char)0;
((void (*)(void *, void *, void *, int, int, int, void *, unsigned int, unsigned int))(void *)__ecereClass_String->_vTbl[__ecereVMethodID_class_OnDisplay])(__ecereClass_String, actualString, surface, x, y, width, (((void *)0)), alignment, (unsigned int)displayFlags);
}
}
