__ecereNameSpace__ecere__gfx__GetDisplaySystem(char * driverName)
{
struct __ecereNameSpace__ecere__com__Class * displayDriver = __ecereNameSpace__ecere__gfx__GetDisplayDriver(driverName);

return displayDriver ? __ecereNameSpace__ecere__com__eClass_GetProperty(displayDriver, "displaySystem") : (((void *)0));
}
