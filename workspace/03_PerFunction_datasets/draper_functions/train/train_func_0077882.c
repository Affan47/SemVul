__ecereNameSpace__ecere__com__eProperty_SelfWatch(struct __ecereNameSpace__ecere__com__Class * _class, char * name, void (* callback)(void *))
{
void * __ecereTemp1;

if(_class)
{
struct __ecereNameSpace__ecere__com__Property * _property = __ecereNameSpace__ecere__com__eClass_FindProperty(_class, name, _class->module);

if(!_property)
_property = __ecereNameSpace__ecere__com__eClass_AddProperty(_class, name, (((void *)0)), (((void *)0)), (((void *)0)), 4);
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&_class->selfWatchers, (__ecereTemp1 = __ecereNameSpace__ecere__com__eSystem_New0(16), ((struct __ecereNameSpace__ecere__com__SelfWatcher *)__ecereTemp1)->_property = _property, ((struct __ecereNameSpace__ecere__com__SelfWatcher *)__ecereTemp1)->callback = callback, ((struct __ecereNameSpace__ecere__com__SelfWatcher *)__ecereTemp1)));
_property->selfWatchable = 0x1;
}
}
