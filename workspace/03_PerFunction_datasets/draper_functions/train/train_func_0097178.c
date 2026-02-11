__ecereRegisterModule_ClipBoard(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(5, "ecere::gui::ClipBoard", 0, sizeof(struct __ecereNameSpace__ecere__gui__ClipBoard), 0, 0, __ecereDestructor___ecereNameSpace__ecere__gui__ClipBoard, module, 1, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass___ecereNameSpace__ecere__gui__ClipBoard = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Allocate", "bool Allocate(unsigned int size)", __ecereMethod___ecereNameSpace__ecere__gui__ClipBoard_Allocate, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Clear", "void Clear()", __ecereMethod___ecereNameSpace__ecere__gui__ClipBoard_Clear, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Load", "bool Load()", __ecereMethod___ecereNameSpace__ecere__gui__ClipBoard_Load, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Save", "bool Save()", __ecereMethod___ecereNameSpace__ecere__gui__ClipBoard_Save, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "Unload", "void Unload()", __ecereMethod___ecereNameSpace__ecere__gui__ClipBoard_Unload, 1);
__ecereNameSpace__ecere__com__eClass_AddDataMember(class, "text", "char *", 8, 8, 1);
__ecereNameSpace__ecere__com__eClass_AddDataMember(class, "handle", "void *", 8, 8, 1);
__ecerePropM___ecereNameSpace__ecere__gui__ClipBoard_memory = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "memory", "char *", 0, __ecereProp___ecereNameSpace__ecere__gui__ClipBoard_Get_memory, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__gui__ClipBoard_memory = __ecerePropM___ecereNameSpace__ecere__gui__ClipBoard_memory, __ecerePropM___ecereNameSpace__ecere__gui__ClipBoard_memory = (void *)0;
}
