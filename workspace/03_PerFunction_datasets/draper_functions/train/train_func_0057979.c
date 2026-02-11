__ecereConstructor___ecereNameSpace__eda__PleaseWait(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__Anchor __simpleStruct1 =
{

{
1, 0LL
},
{
1, 0LL
},
{
1, 0LL
},
{
1, 0LL
}
};
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0 =
{
400, 30
};
struct __ecereNameSpace__eda__PleaseWait * __ecerePointer___ecereNameSpace__eda__PleaseWait = (struct __ecereNameSpace__eda__PleaseWait *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__PleaseWait->offset) : 0);

__ecerePointer___ecereNameSpace__eda__PleaseWait->progress = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__controls__ProgressBar);
__ecereNameSpace__ecere__com__eInstance_IncRef(__ecerePointer___ecereNameSpace__eda__PleaseWait->progress);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_isModal(this, 0x1);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_autoCreate(this, 0x0);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_borderStyle(this, 0x3);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(this, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Please wait while the report is being generated...", (((void *)0))));
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_clientSize(this, &__simpleStruct0);
(__ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(__ecerePointer___ecereNameSpace__eda__PleaseWait->progress, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_anchor(__ecerePointer___ecereNameSpace__eda__PleaseWait->progress, &__simpleStruct1));
return 0x1;
}
