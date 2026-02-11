__ecereMethod___ecereNameSpace__ecere__gfx__DisplaySystem_Lock(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gfx__DisplaySystem * __ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem = (struct __ecereNameSpace__ecere__gfx__DisplaySystem *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx__DisplaySystem->offset) : 0);
unsigned int result = 0x0;

__ecereMethod___ecereNameSpace__ecere__sys__Mutex_Wait(__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->mutex);
if(!__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->current)
result = ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance * displaySystem))__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->driver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_LockSystem])(this);
else
result = 0x1;
__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->current++;
return result;
}
