__ecereDestructor___ecereNameSpace__ecere__net__DCOMClientThread(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__net__DCOMClientThread * __ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread = (struct __ecereNameSpace__ecere__net__DCOMClientThread *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__DCOMClientThread->offset) : 0);

((__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->semaphore ? (__ecereClass___ecereNameSpace__ecere__sys__Semaphore->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__Semaphore->Destructor(__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->semaphore) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->semaphore)) : 0), __ecerePointer___ecereNameSpace__ecere__net__DCOMClientThread->semaphore = 0);
}
