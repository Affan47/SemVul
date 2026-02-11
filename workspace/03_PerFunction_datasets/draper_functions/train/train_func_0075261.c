__ecereProp___ecereNameSpace__ecere__sys__BTNode_Get_next(struct __ecereNameSpace__ecere__sys__BTNode * this)
{
struct __ecereNameSpace__ecere__sys__BTNode * right = this->right;

if(right)
return __ecereProp___ecereNameSpace__ecere__sys__BTNode_Get_minimum(right);
while(this)
{
struct __ecereNameSpace__ecere__sys__BTNode * parent = this->parent;

if(parent && this == parent->left)
return parent;
else
this = parent;
}
return (((void *)0));
}
