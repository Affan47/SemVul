__ecereMethod_ProjectNode_FixupNode(struct ProjectNode * this, char * parentPath)
{
if(!this->parent)
{
this->type = 0;
}
else if(this->nodeType == 0)
{
this->type = 1;
if(!this->path)
{
this->path = __ecereFunction___ecereNameSpace__ecere__sys__CopyString((this->parent->type == 2 || this->parent->type == 3) ? parentPath : "");
}
}
else if(this->nodeType == 1)
{
this->type = 2;
if(!this->path)
{
char temp[797];

strcpy(temp, (this->parent->type == 2 || this->parent->type == 3) ? parentPath : "");
__ecereFunction___ecereNameSpace__ecere__sys__PathCatSlash(temp, this->name);
this->path = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(temp);
}
}
this->indent = this->parent ? this->parent->indent + 1 : 0;
if(this->type == 1)
this->icon = __ecereMethod_NodeIcons_SelectFileIcon(this->name);
else
this->icon = __ecereMethod_NodeIcons_SelectNodeIcon(this->type);
if(this->files)
{
{
struct ProjectNode * f;
struct __ecereNameSpace__ecere__com__Instance * __internalLinkList = this->files;

for(f = ((struct ProjectNode *)((struct __ecereNameSpace__ecere__com__LinkList *)(((char *)__internalLinkList + 24)))->first); f; f = (struct ProjectNode *)((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__IteratorPointer * pointer))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __internalLinkList;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__LinkList->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_GetNext])(__internalLinkList, (struct __ecereNameSpace__ecere__com__IteratorPointer *)f))
{
f->parent = this;
if(this->type == 0)
parentPath[0] = '\0';
else if(this->type == 3 || this->type == 2)
strcpy(parentPath, this->path);
__ecereMethod_ProjectNode_FixupNode(f, parentPath);
}
}
}
}
