ini_special_tokens FCN((language0,tokens))
LANGUAGE language0 C0("")
SPEC HUGE*tokens C1("Array of tokens to be initialized.")
{
SPEC HUGE*s;
int n;
name_pointer np;
LANGUAGE language_tmp= language;

language= language0;


for(s= tokens;(n= STRLEN(s->name))!=0;s++)
{
ASCII HUGE*p= x_to_ASCII(OC(s->name));

s->len= n;
*s->pid= ID_NUM_ptr(np,p,p+n);
np->expandable|= language0;
if(!np->x_translate)np->x_translate=
(X_FCN(HUGE_FCN_PTR*HUGE*)(VOID))get_mem0(OC("x array"),
(unsigned long)(NUM_LANGUAGES),
sizeof(X_FCN(HUGE_FCN_PTR*)(VOID)));
np->x_translate[lan_num(language0)]= s->expand;
}

language= language_tmp;
}
