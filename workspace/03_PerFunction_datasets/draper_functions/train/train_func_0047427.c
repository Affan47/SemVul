__ecereMethod_CompilerTab_OnCreate(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct CompilerTab * __ecerePointer_CompilerTab = (struct CompilerTab *)(this ? (((char *)this) + __ecereClass_CompilerTab->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * buildTab = (struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this);

__ecereMethod_BuildTab_SelectNode(buildTab, ((struct BuildTab *)(((char *)buildTab + __ecereClass_BuildTab->offset)))->lastSelectedNode, 0x1);
return 0x1;
}
