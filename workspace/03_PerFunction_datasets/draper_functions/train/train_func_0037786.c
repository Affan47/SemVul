__ecereMethod___ecereNameSpace__ecere__net__NetworkClientFile_ReadMoreData(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int start, unsigned int size, unsigned int wait)
{
struct __ecereNameSpace__ecere__net__NetworkClientFile * __ecerePointer___ecereNameSpace__ecere__net__NetworkClientFile = (struct __ecereNameSpace__ecere__net__NetworkClientFile *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__NetworkClientFile->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * connection = __ecerePointer___ecereNameSpace__ecere__net__NetworkClientFile->connection;
struct __ecereNameSpace__ecere__net__Request * lastRequestNeeded;

__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Wait(((struct __ecereNameSpace__ecere__net__FileServerConnection *)(((char *)connection + __ecereClass___ecereNameSpace__ecere__net__FileServerConnection->offset)))->mutex);
lastRequestNeeded = __ecereMethod___ecereNameSpace__ecere__net__NetworkClientFile_FigureOutMissingData(this, &start, &size);
if(size)
{
struct __ecereNameSpace__ecere__net__Request * request = __ecereMethod___ecereNameSpace__ecere__net__FileServerConnection_AddRequest(connection, 4, __ecereMethod___ecereNameSpace__ecere__net__Request_ReadResultCallback, this, wait);

request->readStart = start;
request->readSize = size;
__ecereMethod___ecereNameSpace__ecere__net__FileServerConnection_SendReadPacket(connection, __ecerePointer___ecereNameSpace__ecere__net__NetworkClientFile->handle, start, size);
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Release(((struct __ecereNameSpace__ecere__net__FileServerConnection *)(((char *)connection + __ecereClass___ecereNameSpace__ecere__net__FileServerConnection->offset)))->mutex);
if(wait)
{
__ecereMethod___ecereNameSpace__ecere__sys__Semaphore_Wait(request->semaphore);
((request->semaphore ? (__ecereClass___ecereNameSpace__ecere__sys__Semaphore->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__Semaphore->Destructor(request->semaphore) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(request->semaphore)) : 0), request->semaphore = 0);
((request ? (__ecereClass___ecereNameSpace__ecere__net__Request->Destructor ? __ecereClass___ecereNameSpace__ecere__net__Request->Destructor(request) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(request)) : 0), request = 0);
}
}
else
{
if(wait && lastRequestNeeded)
{
if(!lastRequestNeeded->semaphore)
lastRequestNeeded->semaphore = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__sys__Semaphore);
}
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Release(((struct __ecereNameSpace__ecere__net__FileServerConnection *)(((char *)connection + __ecereClass___ecereNameSpace__ecere__net__FileServerConnection->offset)))->mutex);
__ecereMethod___ecereNameSpace__ecere__sys__Semaphore_Wait(lastRequestNeeded->semaphore);
}
}
