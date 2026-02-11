__ecereProp_BuildTab_Get_selectedPlatformName(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct BuildTab * __ecerePointer_BuildTab = (struct BuildTab *)(this ? (((char *)this) + __ecereClass_BuildTab->offset) : 0);

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_created(this))
{
struct __ecereNameSpace__ecere__com__Instance * button = __ecereProp___ecereNameSpace__ecere__gui__controls__SelectorBar_Get_selectedButton(__ecerePointer_BuildTab->platformSelector);

if(button && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_id(button))
{
int platform = (int)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_id(button);
char * platformName = platform ? ((char *  (*)(struct __ecereNameSpace__ecere__com__Class *, void *, char *  tempString, void *  fieldData, unsigned int *  needClass))__ecereClass___ecereNameSpace__ecere__com__Platform->_vTbl[__ecereVMethodID_class_OnGetString])(__ecereClass___ecereNameSpace__ecere__com__Platform, &platform, 0, 0, 0) : (((void *)0));

return platformName;
}
}
return "";
}
