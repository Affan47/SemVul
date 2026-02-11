__ecereConstructor_EditDialog(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__Anchor __simpleStruct3 =
{

{
0, 254LL
},
{
0, 160LL
},
{
0, 0
},
{
0, 0
}
};
struct __ecereNameSpace__ecere__gui__Anchor __simpleStruct2 =
{

{
0, 184LL
},
{
0, 160LL
},
{
0, 0
},
{
0, 0
}
};
struct __ecereNameSpace__ecere__gui__Anchor __simpleStruct1 =
{

{
1, 16LL
},
{
1, 16LL
},
{
1, 18LL
},
{
1, 61LL
}
};
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0 =
{
600, 400
};
struct EditDialog * __ecerePointer_EditDialog = (struct EditDialog *)(this ? (((char *)this) + __ecereClass_EditDialog->offset) : 0);

__ecerePointer_EditDialog->editBox = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__controls__EditBox);
__ecereNameSpace__ecere__com__eInstance_IncRef(__ecerePointer_EditDialog->editBox);
__ecerePointer_EditDialog->saveChanges = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__controls__Button);
__ecereNameSpace__ecere__com__eInstance_IncRef(__ecerePointer_EditDialog->saveChanges);
__ecerePointer_EditDialog->cancel = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__controls__Button);
__ecereNameSpace__ecere__com__eInstance_IncRef(__ecerePointer_EditDialog->cancel);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_borderStyle(this, 0x7);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_size(this, &__simpleStruct0);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_autoCreate(this, 0x0);
(__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(__ecerePointer_EditDialog->editBox, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_anchor(__ecerePointer_EditDialog->editBox, &__simpleStruct1));
(__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(__ecerePointer_EditDialog->saveChanges, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(__ecerePointer_EditDialog->saveChanges, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Save Changes", (((void *)0)))), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_anchor(__ecerePointer_EditDialog->saveChanges, &__simpleStruct2));
(__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(__ecerePointer_EditDialog->cancel, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(__ecerePointer_EditDialog->cancel, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Cancel", (((void *)0)))), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_anchor(__ecerePointer_EditDialog->cancel, &__simpleStruct3));
return 0x1;
}
