__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000053(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * client = __ecereProp___ecereNameSpace__ecere__gui__Window_Get_activeClient(this);
struct __ecereNameSpace__ecere__com__Class * dataType = ((struct __ecereNameSpace__ecere__com__Instance *)(char *)client)->_class;

if(!strcmp(dataType->name, "Designer"))
client = ((struct Designer *)(((char *)((struct __ecereNameSpace__ecere__com__Instance *)client) + __ecereClass_Designer->offset)))->codeEditor;
__ecereMethod___ecereNameSpace__ecere__gui__Window_Activate(client);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_visible(client, 0x1);
return 0x1;
}
