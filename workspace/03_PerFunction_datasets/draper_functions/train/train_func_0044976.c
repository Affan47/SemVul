__ecereMethod___ecereNameSpace__ecere__net__DCOMClientThread_Main(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__net__DCOMClientThread * __ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread = (struct __ecereNameSpace__ecere__net__DCOMClientThread *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__DCOMClientThread->offset) : 0);

((struct __ecereNameSpace__ecere__com__Instance *)(char *)__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->socket)->_refCount += 2;
while(__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->connected)
{
__ecereMethod___ecereNameSpace__ecere__net__Socket_ProcessTimeOut(__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->socket, 0.01);
__ecereMethod___ecereNameSpace__ecere__sys__Semaphore_Release(__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->semaphore);
}
if(((struct __ecereNameSpace__ecere__com__Instance *)(char *)__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->socket)->_refCount > 1)
((struct __ecereNameSpace__ecere__com__Instance *)(char *)__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->socket)->_refCount--;
(__ecereNameSpace__ecere__com__eInstance_DecRef(__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->socket), __ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->socket = 0);
return 0;
}
