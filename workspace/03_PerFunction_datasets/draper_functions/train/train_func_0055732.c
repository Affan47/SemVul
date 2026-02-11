__ecereMethod___ecereNameSpace__ecere__com__Map_Free(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__com__MapNode * node;

while(node = ((struct __ecereNameSpace__ecere__com__MapNode *)((struct __ecereNameSpace__ecere__com__CustomAVLTree *)(((char *)this + 12)))->root))
{
(((void (* )(void *  _class, void *  data))((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[6].dataTypeClass->_vTbl[__ecereVMethodID_class_OnFree])(((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[6].dataTypeClass, __ecereProp___ecereNameSpace__ecere__com__MapNode_Get_value(node)), __ecereProp___ecereNameSpace__ecere__com__MapNode_Set_value(node, 0));
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__IteratorPointer * it))this->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Remove])(this, node);
}
}
