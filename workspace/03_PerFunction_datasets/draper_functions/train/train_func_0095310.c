__ecereProp_Workspace_Set_workspaceFile(struct __ecereNameSpace__ecere__com__Instance * this, char *  value)
{
struct Workspace * __ecerePointer_Workspace = (struct Workspace *)(this ? (((char *)this) + __ecereClass_Workspace->offset) : 0);
char dir[534];

if(__ecerePointer_Workspace->workspaceFile)
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer_Workspace->workspaceFile), __ecerePointer_Workspace->workspaceFile = 0);
if(__ecerePointer_Workspace->workspaceDir)
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer_Workspace->workspaceDir), __ecerePointer_Workspace->workspaceDir = 0);
__ecerePointer_Workspace->workspaceFile = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(value);
__ecereFunction___ecereNameSpace__ecere__sys__StripLastDirectory(__ecerePointer_Workspace->workspaceFile, dir);
__ecerePointer_Workspace->workspaceDir = __ecereFunction___ecereNameSpace__ecere__sys__CopyUnixPath(dir);
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp_Workspace_workspaceFile), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM_Workspace_workspaceFile);
}
