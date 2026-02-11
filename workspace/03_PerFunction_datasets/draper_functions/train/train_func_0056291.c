__ecereMethod___ecereNameSpace__eda__FieldBox_OnKeyDown(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int key, unsigned int ch)
{
struct __ecereNameSpace__eda__FieldBox * __ecerePointer___ecereNameSpace__eda__FieldBox = (struct __ecereNameSpace__eda__FieldBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__FieldBox->offset) : 0);

if((unsigned int)__ecereProp___ecereNameSpace__ecere__gui__Key_Get___ecereNameSpace__ecere__gui__SmartKey(key) == 0x1C)
{
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned int key, unsigned int ch))__ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnKeyDown])(this, key, ch);
return 0x1;
}
else
return ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned int key, unsigned int ch))__ecereClass___ecereNameSpace__ecere__gui__controls__DataBox->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnKeyDown])(this, key, ch);
}
