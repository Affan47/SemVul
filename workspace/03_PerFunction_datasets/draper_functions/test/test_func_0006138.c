__ecereNameSpace__ecere__com___calloc(int n, unsigned int size)
{
void * pointer;

__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Wait(__ecereNameSpace__ecere__com__memMutex);
pointer = (n * size) ? __ecereNameSpace__ecere__com___mycalloc(1, n * size + 2 * 0) : (((void *)0));
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Release(__ecereNameSpace__ecere__com__memMutex);
return pointer ? ((unsigned char *)pointer + 0) : (((void *)0));
}
