__ecereMethod___ecereNameSpace__ecere__sys__BTNode_OnSerialize(struct __ecereNameSpace__ecere__com__Class * class, struct __ecereNameSpace__ecere__sys__BTNode * this, struct __ecereNameSpace__ecere__com__Instance * channel)
{
if((struct __ecereNameSpace__ecere__sys__BTNode *)this)
{
unsigned int __internalValue000;
unsigned int truth = 0x1;

__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass_bool, &truth);
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass_uint, __extension__ ({
__internalValue000 = (unsigned int)this->key;
&__internalValue000;
}));
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass___ecereNameSpace__ecere__sys__BTNode, this->left);
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass___ecereNameSpace__ecere__sys__BTNode, this->right);
}
else
{
unsigned int nothing = 0;

__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Serialize(channel, __ecereClass_uint, &nothing);
}
}
