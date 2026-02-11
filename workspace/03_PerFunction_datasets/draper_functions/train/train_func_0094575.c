__ecereInstMeth___ecereNameSpace__ecere__gui__controls__EditBox_OnHScroll__00000011(struct __ecereNameSpace__ecere__com__Instance * this, int action, int position, unsigned int key)
{
((void (*)(struct __ecereNameSpace__ecere__com__Instance *, int action, int position, unsigned int key))__ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnHScroll])(this, action, position, key);
{
struct __ecereNameSpace__ecere__sys__Point __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Point __simpleStruct0;
struct __ecereNameSpace__ecere__com__Instance * ce = (struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(this);

if(((struct CodeEditor *)(((char *)ce + __ecereClass_CodeEditor->offset)))->openedFileInfo)
__ecereMethod_OpenedFileInfo_ScrollChange(((struct CodeEditor *)(((char *)ce + __ecereClass_CodeEditor->offset)))->openedFileInfo, (__simpleStruct0.x = position, (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_scroll(this, &__simpleStruct1), __simpleStruct0.y = __simpleStruct1.y), &__simpleStruct0));
}
}
