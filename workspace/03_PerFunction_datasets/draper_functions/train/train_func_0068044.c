__ecereMethod_ProjectNode_RenameConfig(struct ProjectNode * this, char * oldName, char * newName)
{
if(this->files)
{
{
struct ProjectNode * f;
struct __ecereNameSpace__ecere__com__Instance * __internalLinkList = this->files;

for(f = ((struct ProjectNode *)((struct __ecereNameSpace__ecere__com__LinkList *)(((char *)__internalLinkList + 24)))->first); f; f = (struct ProjectNode *)((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__IteratorPointer * pointer))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __internalLinkList;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__LinkList->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_GetNext])(__internalLinkList, (struct __ecereNameSpace__ecere__com__IteratorPointer *)f))
if((__ecereProp_ProjectNode_Get_configurations(f) || f->files))
{
__ecereMethod_ProjectNode_RenameConfig(f, oldName, newName);
}
}
}
if(__ecereProp_ProjectNode_Get_configurations(this))
{
{
struct __ecereNameSpace__ecere__com__Iterator c =
{
__ecereProp_ProjectNode_Get_configurations(this), 0
};

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&c))
if(!strcmp(((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&c))->name, oldName))
{
(__ecereNameSpace__ecere__com__eSystem_Delete(((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&c))->name), ((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&c))->name = 0);
((struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&c))->name = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(newName);
}
}
}
}
