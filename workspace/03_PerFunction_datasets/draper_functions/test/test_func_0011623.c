__ecereMethod_CompilerOptionsTab_Load(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct CompilerOptionsTab * __ecerePointer_CompilerOptionsTab = (struct CompilerOptionsTab *)(this ? (((char *)this) + __ecereClass_CompilerOptionsTab->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * compiler = __ecereProp_CompilersSubTab_Get_loadedCompiler(this);

if(compiler)
{
unsigned int disabled = ((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->readOnly;

__ecereProp___ecereNameSpace__ecere__gui__controls__DropBox_Set_currentRow(__ecerePointer_CompilerOptionsTab->targetPlatform, __ecereMethod___ecereNameSpace__ecere__gui__controls__DropBox_FindRow(__ecerePointer_CompilerOptionsTab->targetPlatform, ((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->targetPlatform));
__ecerePointer_CompilerOptionsTab->numJobs = ((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->numJobs;
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataBox_Refresh(__ecerePointer_CompilerOptionsTab->numJobsBox);
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_checked(__ecerePointer_CompilerOptionsTab->ccacheEnabled, ((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->ccacheEnabled);
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_checked(__ecerePointer_CompilerOptionsTab->distccEnabled, ((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->distccEnabled);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer_CompilerOptionsTab->distccHosts, !((struct CompilerConfig *)(((char *)compiler + __ecereClass_CompilerConfig->offset)))->distccEnabled);
__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Set_contents(__ecerePointer_CompilerOptionsTab->distccHosts, __ecereProp_CompilerConfig_Get_distccHosts(compiler));
__ecereProp_StringListBox_Set_strings(__ecerePointer_CompilerOptionsTab->prepDefs, __ecereProp_CompilerConfig_Get_prepDirectives(compiler));
__ecereProp_StringListBox_Set_strings(__ecerePointer_CompilerOptionsTab->excludedLibraries, __ecereProp_CompilerConfig_Get_excludeLibs(compiler));
__ecereProp_StringListBox_Set_strings(__ecerePointer_CompilerOptionsTab->eCcompilerFlags, __ecereProp_CompilerConfig_Get_eCcompilerFlags(compiler));
__ecereProp_StringListBox_Set_strings(__ecerePointer_CompilerOptionsTab->compilerFlags, __ecereProp_CompilerConfig_Get_compilerFlags(compiler));
__ecereProp_StringListBox_Set_strings(__ecerePointer_CompilerOptionsTab->linkerFlags, __ecereProp_CompilerConfig_Get_linkerFlags(compiler));
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer_CompilerOptionsTab->labelTargetPlatform, disabled);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer_CompilerOptionsTab->targetPlatform, disabled);
}
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x0);
}
