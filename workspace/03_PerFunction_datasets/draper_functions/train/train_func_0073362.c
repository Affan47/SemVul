__ecereNameSpace__ecere__com__eModule_LoadStatic(struct __ecereNameSpace__ecere__com__Instance * fromModule, char * name, int importAccess, unsigned int (* Load)(struct __ecereNameSpace__ecere__com__Instance * module), unsigned int (* Unload)(struct __ecereNameSpace__ecere__com__Instance * module))
{
struct __ecereNameSpace__ecere__com__Instance * module;

for(module = ((struct __ecereNameSpace__ecere__com__Application *)(((char *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)fromModule + structSize_Instance)))->application + structSize_Module)))->allModules.first; module; module = ((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + structSize_Instance)))->next)
{
if(!strcmp(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + structSize_Instance)))->name, name))
break;
}
if(!module)
{
if(Load)
{
module = (struct __ecereNameSpace__ecere__com__Instance *)__ecereNameSpace__ecere__com__eInstance_New(__ecereNameSpace__ecere__com__eSystem_FindClass(fromModule, "Module"));
((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + structSize_Instance)))->application = ((struct __ecereNameSpace__ecere__com__Module *)(((char *)fromModule + structSize_Instance)))->application;
((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + structSize_Instance)))->name = __ecereNameSpace__ecere__sys__CopyString(name);
((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + structSize_Instance)))->origImportType = 1;
((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + structSize_Instance)))->Unload = (void *)Unload;
if(!Load(module))
{
__ecereNameSpace__ecere__com__eInstance_Delete((struct __ecereNameSpace__ecere__com__Instance *)module);
module = (((void *)0));
}
}
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&((struct __ecereNameSpace__ecere__com__Application *)(((char *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)fromModule + structSize_Instance)))->application + structSize_Module)))->allModules, module);
}
if(module)
{
if(fromModule)
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&((struct __ecereNameSpace__ecere__com__Module *)(((char *)fromModule + structSize_Instance)))->modules, __extension__ ({
struct __ecereNameSpace__ecere__com__SubModule * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__com__SubModule);

__ecereInstance1->module = module, __ecereInstance1->importMode = importAccess, __ecereInstance1;
}));
}
module->_refCount++;
}
return module;
}
