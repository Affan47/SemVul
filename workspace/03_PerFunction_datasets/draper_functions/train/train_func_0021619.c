__ecereMethod___ecereNameSpace__ecere__com__CustomAVLTree_Add(struct __ecereNameSpace__ecere__com__Instance * this, uint64 node)
{
struct __ecereNameSpace__ecere__com__CustomAVLTree * __ecerePointer___ecereNameSpace__ecere__com__CustomAVLTree = (struct __ecereNameSpace__ecere__com__CustomAVLTree *)(this ? (((char *)this) + 12) : 0);

if(!__ecerePointer___ecereNameSpace__ecere__com__CustomAVLTree->root)
__ecerePointer___ecereNameSpace__ecere__com__CustomAVLTree->root = node;
else
{
struct __ecereNameSpace__ecere__com__Class * Tclass = ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[3].dataTypeClass->templateArgs[0].dataTypeClass;

if(!Tclass)
{
Tclass = ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[3].dataTypeClass->templateArgs[0].dataTypeClass = __ecereNameSpace__ecere__com__eSystem_FindClass(((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 12)))->application, ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[3].dataTypeClass->templateArgs[0].dataTypeString);
}
if(__ecereMethod___ecereNameSpace__ecere__com__AVLNode_Add(__ecerePointer___ecereNameSpace__ecere__com__CustomAVLTree->root, Tclass, node))
__ecerePointer___ecereNameSpace__ecere__com__CustomAVLTree->root = (uint64)(__ecereMethod___ecereNameSpace__ecere__com__AVLNode_Rebalance(node));
else
return (((void *)0));
}
__ecerePointer___ecereNameSpace__ecere__com__CustomAVLTree->count++;
return (struct __ecereNameSpace__ecere__com__IteratorPointer *)node;
}
