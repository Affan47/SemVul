__ecereMethod___ecereNameSpace__ecere__gui__controls__Stacker_SetWindowArea(struct __ecereNameSpace__ecere__com__Instance * this, int * x, int * y, int * w, int * h, int * cw, int * ch)
{
struct __ecereNameSpace__ecere__gui__controls__Stacker * __ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker = (struct __ecereNameSpace__ecere__gui__controls__Stacker *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__Stacker->offset) : 0);

((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int *  x, int *  y, int *  w, int *  h, int *  cw, int *  ch))__ecereClass___ecereNameSpace__ecere__gui__Window->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_SetWindowArea])(this, x, y, w, h, cw, ch);
if(((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->bits & 0x2) >> 1)) && ((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->bits & 0x10) >> 4)))
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;

if(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->direction == 1)
*y += (int)((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_size(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left, &__simpleStruct0), __simpleStruct0.h + 4));
else
*x += (int)((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_size(__ecerePointer___ecereNameSpace__ecere__gui__controls__Stacker->left, &__simpleStruct1), __simpleStruct1.w + 4));
}
}
