__ecereProp_StringListBox_Get_strings(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct StringListBox * __ecerePointer_StringListBox = (struct StringListBox *)(this ? (((char *)this) + __ecereClass_StringListBox->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * array = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__com__Array_TPL_String_);
int c, start = 0;
char * contents = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_contents(this);
char * s;
char ch;
unsigned int quoted = 0x0;

for(c = 0; (ch = contents[c]); c++)
{
if(ch == ' ' && !quoted)
{
if(c - start)
{
if((s = MakeString(contents + start, c - start, __ecerePointer_StringListBox->switchToKeep, __ecerePointer_StringListBox->lenSwitchToKeep)))
((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = array;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(array, (uint64)(s));
}
start = c + 1;
}
else if(ch == '\"')
{
if(quoted)
quoted = 0x0;
else
quoted = 0x1;
}
}
if(c - start)
{
if((s = MakeString(contents + start, c - start, __ecerePointer_StringListBox->switchToKeep, __ecerePointer_StringListBox->lenSwitchToKeep)))
((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = array;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(array, (uint64)(s));
}
return array;
}
