OutputEnumerator(struct Enumerator * enumerator, struct __ecereNameSpace__ecere__com__Instance * f)
{
OutputIdentifier(enumerator->id, f);
if(enumerator->exp)
{
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))f->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(f, " = ");
OutputExpression(enumerator->exp, f);
}
}
