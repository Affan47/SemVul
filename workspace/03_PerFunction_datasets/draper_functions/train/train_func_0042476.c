__ecereNameSpace__ecere__gui__class_OnSaveEdit(struct __ecereNameSpace__ecere__com__Class * _class, void ** data, struct __ecereNameSpace__ecere__com__Instance * editControl, void * object)
{
if(_class->type == 4)
{
struct __ecereNameSpace__ecere__com__Instance * dropBox = (struct __ecereNameSpace__ecere__com__Instance *)editControl;

return __ecereMethod___ecereNameSpace__ecere__gui__controls__DropBox_Save(dropBox);
}
else
{
unsigned int changed = 0x0;
struct __ecereNameSpace__ecere__com__Instance * editBox = (struct __ecereNameSpace__ecere__com__Instance *)editControl;

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_modifiedDocument(editBox) && (!_class->noExpansion || _class->_vTbl[__ecereVMethodID_class_OnGetDataFromString] != (void *)((unsigned int (*)(struct __ecereNameSpace__ecere__com__Class * class, void *, char *  string))__ecereClass___ecereNameSpace__ecere__com__Instance->_vTbl[__ecereVMethodID_class_OnGetDataFromString])))
{
if(_class->type == 0 || _class->type == 5)
{
((void (*)(void *, void *))(void *)_class->_vTbl[__ecereVMethodID_class_OnFree])(_class, *data);
changed = ((unsigned int (*)(void *, void *, const char *))(void *)_class->_vTbl[__ecereVMethodID_class_OnGetDataFromString])(_class, data, __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_text(__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_line(editBox)));
}
else
{
((void (*)(void *, void *))(void *)_class->_vTbl[__ecereVMethodID_class_OnFree])(_class, data);
changed = ((unsigned int (*)(void *, void *, const char *))(void *)_class->_vTbl[__ecereVMethodID_class_OnGetDataFromString])(_class, data, __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_text(__ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_line(editBox)));
}
}
return changed;
}
}
