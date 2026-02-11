__ecereRegisterModule_FindDialog(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(0, "ecere::gui::dialogs::FindDialog", "ecere::gui::Window", sizeof(struct __ecereNameSpace__ecere__gui__dialogs__FindDialog), 0, __ecereConstructor___ecereNameSpace__ecere__gui__dialogs__FindDialog, __ecereDestructor___ecereNameSpace__ecere__gui__dialogs__FindDialog, module, 1, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass___ecereNameSpace__ecere__gui__dialogs__FindDialog = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnKeyHit", 0, __ecereMethod___ecereNameSpace__ecere__gui__dialogs__FindDialog_OnKeyHit, 1);
__ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_editBox = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "editBox", "ecere::gui::controls::EditBox", __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Set_editBox, 0, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_editBox = __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_editBox, __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_editBox = (void *)0;
__ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchString = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "searchString", "char *", __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Set_searchString, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Get_searchString, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchString = __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchString, __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchString = (void *)0;
__ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_wholeWord = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "wholeWord", "bool", __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Set_wholeWord, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Get_wholeWord, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_wholeWord = __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_wholeWord, __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_wholeWord = (void *)0;
__ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_matchCase = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "matchCase", "bool", __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Set_matchCase, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Get_matchCase, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_matchCase = __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_matchCase, __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_matchCase = (void *)0;
__ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchUp = __ecereNameSpace__ecere__com__eClass_AddProperty(class, "searchUp", "bool", __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Set_searchUp, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_Get_searchUp, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application)
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchUp = __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchUp, __ecerePropM___ecereNameSpace__ecere__gui__dialogs__FindDialog_searchUp = (void *)0;
}
