__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000056(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_visible(__ecerePointer_IDEWorkSpace->toolBox, 0x1);
__ecereMethod___ecereNameSpace__ecere__gui__Window_Activate(__ecerePointer_IDEWorkSpace->toolBox);
return 0x1;
}
