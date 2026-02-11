__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_isCheckbox(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int value)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
struct __ecereNameSpace__ecere__gui__controls__Button * __ecerePointer___ecereNameSpace__ecere__gui__controls__Button = (struct __ecereNameSpace__ecere__gui__controls__Button *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__Button->offset) : 0);

if(value)
{
__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle = (__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle & ~0x10) | (((unsigned int)0x1) << 4);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_background(this, 0xFFFFFF);
__ecereMethod___ecereNameSpace__ecere__gui__controls__Button_RemoveRadio(this);
__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle = (__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle & ~0x40) | (((unsigned int)0x0) << 6);
__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle = (__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle & ~0x1) | (((unsigned int)0x0) << 0);
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_opacity(this, 0);
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_drawBehind(this, 0x1);
}
else
__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle = (__ecerePointer___ecereNameSpace__ecere__gui__controls__Button->buttonStyle & ~0x10) | (((unsigned int)0x0) << 4);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__Button->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnLoadGraphics])(this);
__ecereMethod___ecereNameSpace__ecere__gui__Window_SetInitSize(this, (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_initSize(this, &__simpleStruct0), &__simpleStruct0));
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__ecere__gui__controls__Button_isCheckbox), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__ecere__gui__controls__Button_isCheckbox);
}
