__ecereMethod_ProjectView_ProjectSave(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct ProjectView * __ecerePointer_ProjectView = (struct ProjectView *)(this ? (((char *)this) + __ecereClass_ProjectView->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * row = __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_currentRow(__ecerePointer_ProjectView->fileList);
struct ProjectNode * node = row ? (struct ProjectNode *)__ecereProp___ecereNameSpace__ecere__gui__controls__DataRow_Get_tag(row) : (((void *)0));
struct Project * prj = node ? __ecereProp_ProjectNode_Get_project(node) : (((void *)0));

if(prj)
{
__ecereMethod_Project_StopMonitoring(prj);
if(__ecereMethod_Project_Save(prj, prj->filePath))
{
struct Project * modPrj = (((void *)0));

prj->topNode->modified = 0x0;
{
struct __ecereNameSpace__ecere__com__Iterator p =
{
__extension__ ({
char * __ecTemp1 = (__ecereProp_IDEWorkSpace_Get_workspace(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace));

((struct Workspace *)(__ecTemp1 + __ecereClass_Workspace->offset));
})->projects, 0
};

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&p))
{
if(((struct Project *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&p))->topNode->modified)
{
modPrj = ((struct Project *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&p));
break;
}
}
}
if(!modPrj)
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x0);
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
}
__ecereMethod_Project_StartMonitoring(prj);
}
return 0x1;
}
