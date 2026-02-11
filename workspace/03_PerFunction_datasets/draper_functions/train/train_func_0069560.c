__ecereRegisterModule_Condition(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(5, "ecere::Condition", 0, sizeof(struct __ecereNameSpace__ecere__Condition), 0, __ecereConstructor___ecereNameSpace__ecere__Condition, __ecereDestructor___ecereNameSpace__ecere__Condition, module, 1, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass___ecereNameSpace__ecere__Condition = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Signal", "void Signal()", __ecereMethod___ecereNameSpace__ecere__Condition_Signal, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Wait", "void Wait(ecere::sys::Mutex mutex)", __ecereMethod___ecereNameSpace__ecere__Condition_Wait, 1);
__ecerePropM___ecereNameSpace__ecere__Condition_name = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "name", "char *", __ecereProp___ecereNameSpace__ecere__Condition_Set_name, __ecereProp___ecereNameSpace__ecere__Condition_Get_name, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__Condition_name = __ecerePropM___ecereNameSpace__ecere__Condition_name, __ecerePropM___ecereNameSpace__ecere__Condition_name = (void *)0;
}
