__ecereRegisterModule_ecc(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(0, "CompilerApp", "ecere::com::Application", 0, 0, 0, 0, module, 2, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass_CompilerApp = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Main", 0, __ecereMethod_CompilerApp_Main, 1);
}
