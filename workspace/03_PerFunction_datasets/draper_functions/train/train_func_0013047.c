__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_DirtyEnd(struct __ecereNameSpace__ecere__com__Instance * this, int y)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);

if((y - __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY) * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h < __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->startY)
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->startY = (int)((y - __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY) * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h + (((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & 0x4) >> 2)) ? 1 : (((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct0), __simpleStruct0.h + 1) - __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h) / 2)));
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->endY = (int)((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct1), __simpleStruct1.h - 1));
}
