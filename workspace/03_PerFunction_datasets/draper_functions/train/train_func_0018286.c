__ecereInstMeth___ecereNameSpace__ecere__gui__controls__Button_NotifyClicked__00000018(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * button, int x, int y, unsigned int mods)
{
struct CompilerOptionsTab * __ecerePointer_CompilerOptionsTab = (struct CompilerOptionsTab *)(this ? (((char *)this) + __ecereClass_CompilerOptionsTab->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * compiler = __ecereProp_CompilersSubTab_Get_loadedCompiler(this);

if(compiler)
{
((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->ccacheEnabled = __ecereProp___ecereNameSpace__ecere__gui__controls__Button_Get_checked(button);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x1);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(__ecereProp_CompilersSubTab_Get_compilersTab(this), 0x1);
}
return 0x1;
}
