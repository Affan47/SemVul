__ecereMethod___ecereNameSpace__ecere__gui__skins__TVisionSkin_Window_SetWindowArea(struct __ecereNameSpace__ecere__com__Instance * this, int * x, int * y, int * w, int * h, int * cw, int * ch)
{
int __simpleStruct1;
int __simpleStruct0;
int aw = 0, ah = 0;

*x = *y = 0;
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int *  w, int *  h))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__skins__TVisionSkin_Window->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_GetDecorationsSize])(this, &aw, &ah);
if(((unsigned int)((((struct __ecereNameSpace__ecere__gui__Window *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->style & 0x4) >> 2)) && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_state(this) == 0)
{
*x += 8;
*y += 16;
}
if(((unsigned int)((((struct __ecereNameSpace__ecere__gui__Window *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->style & 0x2) >> 1)) && (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_state(this) != 2 || !__ecereProp___ecereNameSpace__ecere__gui__Window_Get_hasMenuBar(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this))))
{
*y += 0;
if(!((unsigned int)((((struct __ecereNameSpace__ecere__gui__Window *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->style & 0x4) >> 2)) && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_state(this) == 0)
if(!0)
*y += 16;
}
if(((unsigned int)((((struct __ecereNameSpace__ecere__gui__Window *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->style & 0x1) >> 0)))
{
*x += 0;
*y += 0;
}
if(((unsigned int)((((struct __ecereNameSpace__ecere__gui__Window *)(((char *)this + __ecereClass___ecereNameSpace__ecere__gui__Window->offset)))->style & 0x2000000) >> 25)))
{
*y += 16;
}
*cw = *w - aw;
*ch = *h - ah;
*cw = (__simpleStruct0 = *cw, (__simpleStruct0 > 0) ? __simpleStruct0 : 0);
*ch = (__simpleStruct1 = *ch, (__simpleStruct1 > 0) ? __simpleStruct1 : 0);
}
