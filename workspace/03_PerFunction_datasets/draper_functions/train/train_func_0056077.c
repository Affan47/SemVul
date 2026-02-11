__ecereMethod_ProjectView_DeleteNode(struct __ecereNameSpace__ecere__com__Instance * this, struct ProjectNode * projectNode)
{
struct ProjectView * __ecerePointer_ProjectView = (struct ProjectView *)(this ? (((char *)this) + __ecereClass_ProjectView->offset) : 0);

if(projectNode->files)
{
struct ProjectNode * child;

while(child = ((struct ProjectNode *)((struct __ecereNameSpace__ecere__com__LinkList *)(((char *)projectNode->files + 24)))->first))
__ecereMethod_ProjectView_DeleteNode(this, child);
}
__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_DeleteRow(__ecerePointer_ProjectView->fileList, projectNode->row);
__ecereMethod_ProjectNode_Delete(projectNode);
}
