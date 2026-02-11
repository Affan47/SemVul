__ecereMethod_BuildTab_ConfigOnRename(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * button, char ** oldName, char ** newName)
{
struct BuildTab * __ecerePointer_BuildTab = (struct BuildTab *)(this ? (((char *)this) + __ecereClass_BuildTab->offset) : 0);
int c, d = 0;
char ch;

for(c = 0; (ch = (*newName)[c]); c++)
{
if(ch == '_' || isalpha(ch) || (isdigit(ch) && d))
(*newName)[d++] = ch;
}
(*newName)[d] = (char)0;
{
unsigned int found = 0x0;

{
struct __ecereNameSpace__ecere__com__Iterator c =
{
__ecereProp_ProjectNode_Get_configurations(project->topNode), 0
};

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&c))
if(((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&c)) != (uint64)(config))
{
if(!(strcasecmp)(((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&c))->name, *newName))
{
found = 0x1;
break;
}
}
}
if(found || !(*newName)[0])
{
char tmp[1025];
char * tmpName = config->name;

config->name = (((void *)0));
__ecereMethod_BuildTab_FindUniqueConfigName(this, "NewConfig", 0x0, tmp);
config->name = tmpName;
(__ecereNameSpace__ecere__com__eSystem_Delete(*newName), *newName = 0);
*newName = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(tmp);
}
}
if(__ecerePointer_BuildTab->activeConfigName && !strcmp(__ecerePointer_BuildTab->activeConfigName, *oldName))
{
(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer_BuildTab->activeConfigName), __ecerePointer_BuildTab->activeConfigName = 0);
__ecerePointer_BuildTab->activeConfigName = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(*newName);
}
__ecereMethod_ProjectNode_RenameConfig(project->topNode, config->name, *newName);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x1);
return 0x1;
}
