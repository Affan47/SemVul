__ecerePropertySelfWatcher_2_hasHorzScroll(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_hasHorzScroll(this))
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style = (__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & ~0x40) | (((unsigned int)0x1) << 6);
}
