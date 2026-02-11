FindModule(struct __ecereNameSpace__ecere__com__Instance * moduleToFind)
{
struct ModuleImport * module;

if(!((struct __ecereNameSpace__ecere__com__Module *)(((char *)moduleToFind + 24)))->name)
return mainModule;
for(module = (*imports).first; module; module = module->next)
if(module->name && !strcmp(module->name, ((struct __ecereNameSpace__ecere__com__Module *)(((char *)moduleToFind + 24)))->name))
break;
if(!module)
{
module = __extension__ ({
struct ModuleImport * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_ModuleImport);

__ecereInstance1->name = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(((struct __ecereNameSpace__ecere__com__Module *)(((char *)moduleToFind + 24)))->name), __ecereInstance1->importType = ((struct __ecereNameSpace__ecere__com__Module *)(((char *)moduleToFind + 24)))->importType, __ecereInstance1->importAccess = ModuleAccess(privateModule, moduleToFind) ? 1 : 2, __ecereInstance1;
});
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add((&*imports), module);
}
return module;
}
