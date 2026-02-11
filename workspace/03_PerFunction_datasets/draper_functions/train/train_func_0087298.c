__ecereMethod___ecereNameSpace__ecere__PaneSplitter_OnMouseMove(struct __ecereNameSpace__ecere__com__Instance * this, int x, int y, unsigned int mods)
{
struct __ecereNameSpace__ecere__PaneSplitter * __ecerePointer___ecereNameSpace__ecere__PaneSplitter = (struct __ecereNameSpace__ecere__PaneSplitter *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__PaneSplitter->offset) : 0);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_cursor(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), __ecereProp___ecereNameSpace__ecere__gui__Window_Get_cursor(this));
if(__ecerePointer___ecereNameSpace__ecere__PaneSplitter->sliding)
{
unsigned int oldScale = __ecerePointer___ecereNameSpace__ecere__PaneSplitter->scale;

__ecerePointer___ecereNameSpace__ecere__PaneSplitter->scale = 0x0;
if(__ecerePointer___ecereNameSpace__ecere__PaneSplitter->orientation == 1)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct3;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct2;
struct __ecereNameSpace__ecere__sys__Point __simpleStruct1;
int __simpleStruct0;

(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_absPosition(this, &__simpleStruct1), x += __simpleStruct1.x);
x -= __ecerePointer___ecereNameSpace__ecere__PaneSplitter->startPos;
x += __ecerePointer___ecereNameSpace__ecere__PaneSplitter->startX;
x = ((x > 20) ? x : 20);
x = (__simpleStruct0 = (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), &__simpleStruct2), __simpleStruct2.w - 20), (x < __simpleStruct0) ? x : __simpleStruct0);
__ecereProp___ecereNameSpace__ecere__PaneSplitter_Set_split(this, x);
__ecerePointer___ecereNameSpace__ecere__PaneSplitter->scaleSplit = (double)(double)x / (double)(double)(int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), &__simpleStruct3), __simpleStruct3).w;
}
else
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct3;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct2;
struct __ecereNameSpace__ecere__sys__Point __simpleStruct1;
int __simpleStruct0;

(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_absPosition(this, &__simpleStruct1), y += __simpleStruct1.y);
y -= __ecerePointer___ecereNameSpace__ecere__PaneSplitter->startPos;
y += __ecerePointer___ecereNameSpace__ecere__PaneSplitter->startX;
y = ((y > 20) ? y : 20);
y = (__simpleStruct0 = (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), &__simpleStruct2), __simpleStruct2.h - 20), (y < __simpleStruct0) ? y : __simpleStruct0);
__ecereProp___ecereNameSpace__ecere__PaneSplitter_Set_split(this, y);
__ecerePointer___ecereNameSpace__ecere__PaneSplitter->scaleSplit = (double)(double)y / (double)(double)(int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this), &__simpleStruct3), __simpleStruct3).h;
}
__ecerePointer___ecereNameSpace__ecere__PaneSplitter->scale = oldScale;
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, struct __ecereNameSpace__ecere__com__Instance * splitter))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__PaneSplitter->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__PaneSplitter_NotifyResized])(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this), this);
}
return 0x1;
}
