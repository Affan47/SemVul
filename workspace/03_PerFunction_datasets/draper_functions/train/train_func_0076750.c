__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Set_wrap(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int value)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style = (__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & ~0x10000) | (((unsigned int)value) << 16);
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, (((void *)0)));
__ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_wrap), __ecereNameSpace__ecere__com__eInstance_FireSelfWatchers(this, __ecerePropM___ecereNameSpace__ecere__gui__controls__EditBox_wrap);
}
