__ecereInstMeth___ecereNameSpace__ecere__gui__controls__EditBox_OnActivate__00000003(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int active, struct __ecereNameSpace__ecere__com__Instance * previous, unsigned int * goOnWithActivation, unsigned int direct)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);

__ecereProp___ecereNameSpace__ecere__gui__Window_Set_opacity(this, (active && !__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_readOnly(this)) ? 1.0f : __ecereProp___ecereNameSpace__ecere__gui__Window_Get_opacity(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this)));
return ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned int active, struct __ecereNameSpace__ecere__com__Instance * previous, unsigned int *  goOnWithActivation, unsigned int direct))__ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnActivate])(this, active, previous, goOnWithActivation, direct);
}
