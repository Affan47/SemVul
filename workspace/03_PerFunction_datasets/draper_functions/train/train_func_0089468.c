__ecereMethod___ecereNameSpace__eda__EditSection_InitFields(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__eda__EditSection * __ecerePointer___ecereNameSpace__eda__EditSection = (struct __ecereNameSpace__eda__EditSection *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__EditSection->offset) : 0);
struct __ecereNameSpace__ecere__sys__OldLink * link;

for(link = __ecerePointer___ecereNameSpace__eda__EditSection->editBoxes.first; link; link = link->next)
{
struct __ecereNameSpace__ecere__com__Instance * dataBox = link->data;

__ecereMethod___ecereNameSpace__eda__FieldDataBox_Init(dataBox);
}
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * editSection))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__eda__EditSection->_vTbl;
})[__ecereVMethodID___ecereNameSpace__eda__EditSection_NotifyInitFields])(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this), this);
}
