__ecereMethod_Sheet_AddMethodClicked(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * button, int x, int y, unsigned int mods)
{
struct Sheet * __ecerePointer_Sheet = (struct Sheet *)(this ? (((char *)this) + __ecereClass_Sheet->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * row = (struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_id(button);
struct CodeObject * object = (struct CodeObject *)__ecereMethod___ecereNameSpace__ecere__gui__controls__DataRow_GetData(row, __ecerePointer_Sheet->methodName);

__ecereMethod_CodeEditor_AddMethod(__ecerePointer_Sheet->codeEditor, object->method);
return 0x1;
}
