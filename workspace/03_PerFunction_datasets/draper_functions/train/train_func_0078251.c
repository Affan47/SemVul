__ecereMethod___ecereNameSpace__ecere__sys__StringBTNode_OnUnserialize(struct __ecereNameSpace__ecere__com__Class * class, struct __ecereNameSpace__ecere__sys__StringBTNode ** this, struct __ecereNameSpace__ecere__com__Instance * channel)
{
unsigned int truth;

__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass_bool, &truth);
if(truth)
{
(*(this)) = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__sys__StringBTNode);
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass_String, &(*(this))->key);
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass___ecereNameSpace__ecere__sys__StringBTNode, &(*(this))->left);
if((*(this))->left)
{
(*(this))->left->parent = (void *)*(struct __ecereNameSpace__ecere__sys__StringBTNode **)this;
}
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass___ecereNameSpace__ecere__sys__StringBTNode, &(*(this))->right);
if((*(this))->right)
{
(*(this))->right->parent = (void *)*(struct __ecereNameSpace__ecere__sys__StringBTNode **)this;
}
(*(this))->depth = __ecereProp___ecereNameSpace__ecere__sys__BTNode_Get_depthProp(((struct __ecereNameSpace__ecere__sys__BTNode *)((void *)*(struct __ecereNameSpace__ecere__sys__StringBTNode **)this)));
}
else
(*(this)) = (((void *)0));
}
