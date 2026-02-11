__ecereMethod___ecereNameSpace__ecere__net__DCOMService_Stop(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__net__DCOMService * __ecerePointer___ecereNameSpace__ecere__net__DCOMService = (struct __ecereNameSpace__ecere__net__DCOMService *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__DCOMService->offset) : 0);
unsigned int result = 0x1;
struct __ecereNameSpace__ecere__com__Instance * socket;

((struct __ecereNameSpace__ecere__net__DCOMServiceThread *)(((char *)__ecerePointer___ecereNameSpace__ecere__net__DCOMService->thread + __ecereClass___ecereNameSpace__ecere__net__DCOMServiceThread->offset)))->connected = 0x0;
result = __ecereMethod___ecereNameSpace__ecere__net__Service_Stop(this);
if(((struct __ecereNameSpace__ecere__sys__Thread *)(((char *)__ecerePointer___ecereNameSpace__ecere__net__DCOMService->thread + __ecereClass___ecereNameSpace__ecere__sys__Thread->offset)))->started && __ecereNameSpace__ecere__sys__GetCurrentThreadID() != (long long)((struct __ecereNameSpace__ecere__sys__Thread *)(((char *)__ecerePointer___ecereNameSpace__ecere__net__DCOMService->thread + __ecereClass___ecereNameSpace__ecere__sys__Thread->offset)))->id)
__ecereMethod___ecereNameSpace__ecere__sys__Thread_Wait(__ecerePointer___ecereNameSpace__ecere__net__DCOMService->thread);
return result;
}
