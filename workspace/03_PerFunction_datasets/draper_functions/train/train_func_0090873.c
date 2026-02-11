__ecereNameSpace__ecere__com___realloc(void * pointer, unsigned int size)
{
if(!size)
{
__ecereNameSpace__ecere__com___free(pointer);
return (((void *)0));
}
pointer = __ecereNameSpace__ecere__com___myrealloc(pointer, size);
return pointer ? ((unsigned char *)pointer + 0) : (((void *)0));
}
