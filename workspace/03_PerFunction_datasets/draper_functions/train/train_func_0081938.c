__ecereMethod___ecereNameSpace__ecere__net__Socket_Send(struct __ecereNameSpace__ecere__com__Instance * this, void * buffer, int size)
{
struct __ecereNameSpace__ecere__net__Socket * __ecerePointer___ecereNameSpace__ecere__net__Socket = (struct __ecereNameSpace__ecere__net__Socket *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__net__Socket->offset) : 0);

if(this)
{
SOCKET s = __ecerePointer___ecereNameSpace__ecere__net__Socket->s;
int count;
fd_set ws, es;

if(s != -1 && ((__ecerePointer___ecereNameSpace__ecere__net__Socket->type == 0 && (count = ((int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned char *  buffer, int count, unsigned int flags))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__net__Socket->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__net__Socket_SendData])(this, buffer, size, 0))) || (__ecerePointer___ecereNameSpace__ecere__net__Socket->type == 1 && (count = (int)sendto(s, buffer, size, 0, (SOCKADDR *)&__ecerePointer___ecereNameSpace__ecere__net__Socket->a, sizeof __ecerePointer___ecereNameSpace__ecere__net__Socket->a)))))
{
do
{
int __d0, __d1;

__asm__ volatile("cld; rep; stosq":"=c"(__d0),"=D"(__d1):"a"(0),"0"(sizeof(fd_set) / sizeof(__fd_mask)),"1"(&(*(&ws)).__fds_bits[0]):"memory");

}while(0);
do
{
int __d0, __d1;

__asm__ volatile("cld; rep; stosq":"=c"(__d0),"=D"(__d1):"a"(0),"0"(sizeof(fd_set) / sizeof(__fd_mask)),"1"(&(*(&es)).__fds_bits[0]):"memory");

}while(0);
((void)((*(&ws)).__fds_bits[((s) / (8 * (int)sizeof(__fd_mask)))] |= (1 << ((s) % (8 * (int)sizeof(__fd_mask))))));
((void)((*(&es)).__fds_bits[((s) / (8 * (int)sizeof(__fd_mask)))] |= (1 << ((s) % (8 * (int)sizeof(__fd_mask))))));
{
}
return 0x1;
}
}
return 0x0;
}
