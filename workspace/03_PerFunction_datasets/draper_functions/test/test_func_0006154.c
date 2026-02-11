__ecereConstructor___ecereNameSpace__eda__DropDataBox(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
struct __ecereNameSpace__eda__DropDataBox * __ecerePointer___ecereNameSpace__eda__DropDataBox = (struct __ecereNameSpace__eda__DropDataBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__DropDataBox->offset) : 0);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_size(this, (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_size(this, &__simpleStruct0), __simpleStruct0.h = 24, &__simpleStruct0));
((struct __ecereNameSpace__ecere__gui__controls__DataBox *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset)))->keepEditor = 0x1;
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_borderStyle(this, 0x8);
__ecerePointer___ecereNameSpace__eda__DropDataBox->showNone = 0x0;
return 0x1;
}
