__ecereMethod___ecereNameSpace__ecere__gui__controls__ListBox_OnApplyGraphics(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
struct __ecereNameSpace__ecere__gui__controls__ListBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox = (struct __ecereNameSpace__ecere__gui__controls__ListBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ListBox->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gui__Window_SetScrollLineStep(this, 8, __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->rowHeight);
if(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->style & 0x1) >> 0)))
{
struct __ecereNameSpace__ecere__com__Instance * field;

for(field = __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->fields.first; field; field = __ecereProp___ecereNameSpace__ecere__gui__controls__DataField_Get_next(field))
{
if(((struct __ecereNameSpace__ecere__gui__controls__DataField *)(((char *)field + __ecereClass___ecereNameSpace__ecere__gui__controls__DataField->offset)))->headButton)
{
__ecereProp___ecereNameSpace__ecere__gui__controls__Button_Set_bevel(((struct __ecereNameSpace__ecere__gui__controls__DataField *)(((char *)field + __ecereClass___ecereNameSpace__ecere__gui__controls__DataField->offset)))->headButton, (!__ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Get_textMode(__ecereNameSpace__ecere__gui__guiApp) && !((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->style & 0x200) >> 9))));
if(__ecereProp___ecereNameSpace__ecere__gui__GuiApplication_Get_textMode(__ecereNameSpace__ecere__gui__guiApp))
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_background(((struct __ecereNameSpace__ecere__gui__controls__DataField *)(((char *)field + __ecereClass___ecereNameSpace__ecere__gui__controls__DataField->offset)))->headButton, ((((unsigned int)((unsigned char)0)) << 16) | (((unsigned int)((unsigned char)170)) << 8) | ((unsigned int)((unsigned char)0))));
}
}
}
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int width, int height))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__ListBox->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnResize])(this, (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct0), __simpleStruct0).w, (int)(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct1), __simpleStruct1).h);
}
