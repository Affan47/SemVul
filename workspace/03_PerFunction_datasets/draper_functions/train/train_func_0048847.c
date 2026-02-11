__ecereMethod___ecereNameSpace__ecere__net__Socket_Disconnect(struct __ecereNameSpace__ecere__com__Instance * this, int code)
{
struct __ecereNameSpace__ecere__net__Socket * __ecerePointer___ecereNameSpace__ecere__net__Socket = (struct __ecereNameSpace__ecere__net__Socket *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__Socket->offset) : 0);

if(this)
{
unsigned int wasDisconnected = __ecerePointer___ecereNameSpace__ecere__net__Socket->disconnected;
SOCKET s = __ecerePointer___ecereNameSpace__ecere__net__Socket->s;

__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Wait(__ecereNameSpace__ecere__net__network.mutex);
__ecerePointer___ecereNameSpace__ecere__net__Socket->disconnectCode = code;
__ecerePointer___ecereNameSpace__ecere__net__Socket->destroyed = 0x1;
if(!__ecerePointer___ecereNameSpace__ecere__net__Socket->disconnected)
{
__ecerePointer___ecereNameSpace__ecere__net__Socket->disconnected = 0x1;
if(!__ecerePointer___ecereNameSpace__ecere__net__Socket->service)
{
if(__ecerePointer___ecereNameSpace__ecere__net__Socket->_connected)
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Remove(((__ecerePointer___ecereNameSpace__ecere__net__Socket->_connected == -1) ? &__ecereNameSpace__ecere__net__network.connectSockets : &__ecereNameSpace__ecere__net__network.sockets), this);
}
else
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Remove(&((struct __ecereNameSpace__ecere__net__Service *)(((char *)__ecerePointer___ecereNameSpace__ecere__net__Socket->service + __ecereClass___ecereNameSpace__ecere__net__Service->offset)))->sockets, this);
__ecerePointer___ecereNameSpace__ecere__net__Socket->service = (((void *)0));
}
__ecerePointer___ecereNameSpace__ecere__net__Socket->_connected = 0;
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Release(__ecereNameSpace__ecere__net__network.mutex);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int code))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__net__Socket->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__net__Socket_OnDisconnect])(this, __ecerePointer___ecereNameSpace__ecere__net__Socket->disconnectCode);
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Wait(__ecereNameSpace__ecere__net__network.mutex);
}
if(s == __ecereNameSpace__ecere__net__network.ns - 1)
__ecereNameSpace__ecere__net__Network_DetermineMaxSocket();
if(s != -1)
{
((void)((*(&__ecereNameSpace__ecere__net__network.readSet)).__fds_bits[((s) / (8 * (int)sizeof(__fd_mask)))] &= ~(1 << ((s) % (8 * (int)sizeof(__fd_mask))))));
((void)((*(&__ecereNameSpace__ecere__net__network.writeSet)).__fds_bits[((s) / (8 * (int)sizeof(__fd_mask)))] &= ~(1 << ((s) % (8 * (int)sizeof(__fd_mask))))));
((void)((*(&__ecereNameSpace__ecere__net__network.exceptSet)).__fds_bits[((s) / (8 * (int)sizeof(__fd_mask)))] &= ~(1 << ((s) % (8 * (int)sizeof(__fd_mask))))));
}
shutdown(s, 2);
if(!wasDisconnected)
(__ecereNameSpace__ecere__com__eInstance_DecRef(this), this = 0);
__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Release(__ecereNameSpace__ecere__net__network.mutex);
}
}
