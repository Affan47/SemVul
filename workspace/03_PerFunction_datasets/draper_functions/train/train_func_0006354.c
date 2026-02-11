__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_OnUnserialize(struct __ecereNameSpace__ecere__com__Class * class, struct __ecereNameSpace__ecere__sys__BinaryTree * this, struct __ecereNameSpace__ecere__com__Instance * channel)
{
__ecereMethod___ecereNameSpace__ecere__com__IOChannel_Unserialize(channel, __ecereClass___ecereNameSpace__ecere__sys__BTNode, &(*this).root);
(*this).count = (*this).root ? __ecereProp___ecereNameSpace__ecere__sys__BTNode_Get_count((*this).root) : 0;
}
