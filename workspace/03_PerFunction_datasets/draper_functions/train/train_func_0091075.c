__ecereMethod___ecereNameSpace__ecere__gui__controls__Stacker_OnVScroll(struct __ecereNameSpace__ecere__com__Instance * this, int action, int position, unsigned int key)
{
struct __ecereNameSpace__ecere__gui__controls__Stacker * __ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker = (struct __ecereNameSpace__ecere__gui__controls__Stacker *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__Stacker->offset) : 0);

if(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->bits & 0x10) >> 4)))
{
unsigned int ld = 0x0, rd = 0x0;

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left, 0x0);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->right, 0x0);
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->direction == 0)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;

if(position == 0)
ld = 0x1;
if(position + (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct0), __simpleStruct0).w >= (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_scrollArea(this, &__simpleStruct1), __simpleStruct1).w)
rd = 0x1;
}
else
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;

if(position == 0)
ld = 0x1;
if(position + (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct0), __simpleStruct0).h >= (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_scrollArea(this, &__simpleStruct1), __simpleStruct1).h)
rd = 0x1;
}
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_disabled(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left) != ld)
{
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left, ld);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int x, int y, unsigned int mods))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__RepButton->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnLeftButtonUp])(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left, -1, 0, 0);
}
if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_disabled(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->right) != rd)
{
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->right, rd);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int x, int y, unsigned int mods))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->right;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__RepButton->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnLeftButtonUp])(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->right, -1, 0, 0);
}
}
}
