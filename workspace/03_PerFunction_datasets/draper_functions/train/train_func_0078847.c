__ecereRegisterModule_DynamicString(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(0, "DynamicString", "ecere::com::Array<char>", 0, 0, __ecereConstructor_DynamicString, 0, module, 1, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass_DynamicString = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnGetString", 0, __ecereMethod_DynamicString_OnGetString, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnGetDataFromString", 0, __ecereMethod_DynamicString_OnGetDataFromString, 1);
__ecereProp_DynamicString_String = __ecereNameSpace__ecere__com__eClass_AddProperty(class, 0, "String", __ecereProp_DynamicString_Set_String, __ecereProp_DynamicString_Get_String, 2);
}
