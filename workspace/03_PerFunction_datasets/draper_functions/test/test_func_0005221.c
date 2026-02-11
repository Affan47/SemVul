OutputEnumerator(struct Enumerator * enumerator, struct __ecereNameSpace__ecere__com__Instance * f)
{
OutputIdentifier(enumerator->id, f);
if(enumerator->exp)
{
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = f;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(f, " = ");
OutputExpression(enumerator->exp, f);
}
}
