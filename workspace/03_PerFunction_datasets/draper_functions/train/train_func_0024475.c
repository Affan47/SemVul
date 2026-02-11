__ecereMethod_IDEApp_Init(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct IDEApp * __ecerePointer_IDEApp = (struct IDEApp *)(this ? (((char *)this) + __ecereClass_IDEApp->offset) : 0);
char ext[17];

__ecereFunction___ecereNameSpace__ecere__sys__SetLoggingMode(1, (((void *)0)));
((int (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = settingsContainer;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass_IDESettingsContainer->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__GlobalSettings_Load])(settingsContainer);
if(((struct __ecereNameSpace__ecere__com__Application *)(((char *)this + 560)))->argc > 1 && !(strcasecmp)(__ecereFunction___ecereNameSpace__ecere__sys__GetExtension(((struct __ecereNameSpace__ecere__com__Application *)(((char *)this + 560)))->argv[1], ext), "3ds"))
{
__ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Set_driver((((struct __ecereNameSpace__ecere__com__Instance *)__thisModule)), "OpenGL");
__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->driverItems[1], 0x1);
}
else
{
__ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Set_driver((((struct __ecereNameSpace__ecere__com__Instance *)__thisModule)), (((struct IDESettings *)(((char *)ideSettings + __ecereClass_IDESettings->offset)))->displayDriver && !strcmp(((struct IDESettings *)(((char *)ideSettings + __ecereClass_IDESettings->offset)))->displayDriver, "OpenGL")) ? ((struct IDESettings *)(((char *)ideSettings + __ecereClass_IDESettings->offset)))->displayDriver : "X");
__ecereProp___ecereNameSpace__ecere__gui__controls__MenuItem_Set_checked(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->driverItems[((struct IDESettings *)(((char *)ideSettings + __ecereClass_IDESettings->offset)))->displayDriver && !strcmp(((struct IDESettings *)(((char *)ideSettings + __ecereClass_IDESettings->offset)))->displayDriver, "OpenGL")], 0x1);
}
__ecereFunction_SetInIDE(0x1);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(__ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Get_desktop(this), (__ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Ecere IDE", (((void *)0)))));
if(!__ecereMethod_IDEApp_LoadIncludeFile(this))
__ecereFunction___ecereNameSpace__ecere__com__PrintLn(__ecereClass_char__PTR_, "error: unable to load :crossplatform.mk file inside ide binary.", (void *)0);
return 0x1;
}
