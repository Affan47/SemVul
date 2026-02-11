__ecereProp___ecereNameSpace__ecere__gui__controls__DropBox_Set_maxShown(struct __ecereNameSpace__ecere__com__Instance * this, int value)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct3;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct2;
struct __ecereNameSpace__ecere__sys__Point __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Point __simpleStruct0;
struct __ecereNameSpace__ecere__gui__controls__DropBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox = (struct __ecereNameSpace__ecere__gui__controls__DropBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__DropBox->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__controls__DropBox->listBoxMaxShown = value;
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int x, int y, int width, int height))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__DropBox->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnPosition])(this, (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_position(this, &__simpleStruct0), __simpleStruct0).x, (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_position(this, &__simpleStruct1), __simpleStruct1).y, (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct2), __simpleStruct2).w, (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct3), __simpleStruct3).h);
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__ecere__gui__controls__DropBox_maxShown), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__ecere__gui__controls__DropBox_maxShown);
}
