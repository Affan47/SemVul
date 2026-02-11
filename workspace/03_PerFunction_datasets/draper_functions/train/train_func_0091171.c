__ecereDestructor___ecereNameSpace__ecere__gfx__DisplaySystem(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gfx__DisplaySystem * __ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem = (struct __ecereNameSpace__ecere__gfx__DisplaySystem *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx__DisplaySystem->offset) : 0);

{
if(__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->driverData)
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->driver->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gfx__DisplayDriver_DestroyDisplaySystem])(this);
if(__ecereNameSpace__ecere__com__eClass_GetProperty(__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->driver, "displaySystem") == this)
__ecereNameSpace__ecere__com__eClass_SetProperty(__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->driver, "displaySystem", (long long)(((void *)0)));
}
((__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->mutex ? (__ecereClass___ecereNameSpace__ecere__sys__Mutex->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__Mutex->Destructor(__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->mutex) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->mutex)) : 0), __ecerePointer___ecereNameSpace__ecere__gfx__DisplaySystem->mutex = 0);
}
