__ecereNameSpace__ecere__com___free(void * pointer)
{
if(pointer)
{
if(__ecereNameSpace__ecere__com__memMutex != pointer)
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Wait(__ecereNameSpace__ecere__com__memMutex);
__ecereNameSpace__ecere__com___myfree(pointer);
if(__ecereNameSpace__ecere__com__memMutex != pointer)
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Release(__ecereNameSpace__ecere__com__memMutex);
}
}
