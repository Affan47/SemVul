__ecereRegisterModule_MemoryEDB(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(0, "MemoryEDB_ec}eda::EDBMemoryDataSource", "eda::DataSourceDriver", 0, 0, 0, 0, module, 3, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass___ecereNameSpace__eda__EDBMemoryDataSource = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OpenDatabase", 0, __ecereMethod___ecereNameSpace__eda__EDBMemoryDataSource_OpenDatabase, 1);
{
struct __ecereNameSpace__ecere__com__Class * _class = __ecereNameSpace__ecere__com__eSystem_FindClass(module, "EDBMemoryDataSource");

__ecereNameSpace__ecere__com__eClass_SetProperty(_class, "name", (long long)"MemoryEDB");
}
}
