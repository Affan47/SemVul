__ecereMethod___ecereNameSpace__ecere__com__Container_TakeOut(struct __ecereNameSpace__ecere__com__Instance * this, uint64 d)
{
struct __ecereNameSpace__ecere__com__IteratorPointer * i = ((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))this->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Find])(this, d);

if(i)
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__IteratorPointer * it))this->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Remove])(this, i);
}
