FreeTypeData(struct __ecereNameSpace__ecere__com__Instance * privateModule)
{
struct __ecereNameSpace__ecere__com__Instance * m;

for(m = ((struct __ecereNameSpace__ecere__com__Application *)(((char *)((struct __ecereNameSpace__ecere__com__Module *)(((char *)privateModule + 24)))->application + 560)))->allModules.first; m; m = ((struct __ecereNameSpace__ecere__com__Module *)(((char *)m + 24)))->next)
{
FreeModuleData(m);
}
FreeModuleData(privateModule);
}
