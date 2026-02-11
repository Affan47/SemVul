__ecereProp___ecereNameSpace__ecere__ToolTip_Set_tip(struct __ecereNameSpace__ecere__com__Instance * this, char * value)
{
struct __ecereNameSpace__ecere__ToolTip * __ecerePointer___ecereNameSpace__ecere__ToolTip = (struct __ecereNameSpace__ecere__ToolTip *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__ToolTip->offset) : 0);

(__ecereNameSpace__ecere__com__eSystem_Delete(__ecerePointer___ecereNameSpace__ecere__ToolTip->tip), __ecerePointer___ecereNameSpace__ecere__ToolTip->tip = 0);
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__ToolTip->lines;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])(__ecerePointer___ecereNameSpace__ecere__ToolTip->lines);
if(value)
{
int c;
char ch, next;
int start = 0;

__ecerePointer___ecereNameSpace__ecere__ToolTip->tip = __ecereNameSpace__ecere__sys__CopyString(value);
next = __ecerePointer___ecereNameSpace__ecere__ToolTip->tip[0];
for(c = 0; ch = next; c++)
{
next = __ecerePointer___ecereNameSpace__ecere__ToolTip->tip[c + 1];
if(ch == '\n' || next == '\0')
{
struct __ecereNameSpace__ecere__ToolTipTextLine __simpleStruct0 =
{
0, 0, 0
};

((struct __ecereNameSpace__ecere__com__IteratorPointer * (*)(struct __ecereNameSpace__ecere__com__Instance *, uint64 value))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__ToolTip->lines;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Array->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Add])(__ecerePointer___ecereNameSpace__ecere__ToolTip->lines, ((__simpleStruct0.string = __ecerePointer___ecereNameSpace__ecere__ToolTip->tip + start, __simpleStruct0.len = c - start + (next == '\0'), &__simpleStruct0)));
start = c + 1;
}
}
}
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__ecere__ToolTip_tip), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__ecere__ToolTip_tip);
}
