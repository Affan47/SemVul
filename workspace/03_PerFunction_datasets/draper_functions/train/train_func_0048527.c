__ecereInstMeth___ecereNameSpace__ecere__gui__controls__DataBox_OnActivate__00000016(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int active, struct __ecereNameSpace__ecere__com__Instance * previous, unsigned int * goOnWithActivation, unsigned int direct)
{
struct __ecereNameSpace__ecere__gui__controls__DataBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__DataBox = (struct __ecereNameSpace__ecere__gui__controls__DataBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->offset) : 0);

if(!active)
{
if(!__ecereMethod___ecereNameSpace__ecere__gui__controls__DataBox_SaveData(this))
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataBox_Refresh(this);
}
return 0x1;
}
