__ecereMethod___ecereNameSpace__ecere__sys__BTNode_Free(struct __ecereNameSpace__ecere__sys__BTNode * this, void (* FreeKey)(void * key))
{
if(this->left)
__ecereMethod___ecereNameSpace__ecere__sys__BTNode_Free(this->left, FreeKey);
if(this->right)
__ecereMethod___ecereNameSpace__ecere__sys__BTNode_Free(this->right, FreeKey);
if(FreeKey)
FreeKey((void *)this->key);
((this ? (__ecereClass___ecereNameSpace__ecere__sys__BTNode->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__BTNode->Destructor(this) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(this)) : 0), this = 0);
}
