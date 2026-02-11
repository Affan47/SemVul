uses_varargs(Declarator * declarator)
{
    Parameter *p;

    return (p = declarator->params.first) != NULL
	&& (p->next == NULL)
	&& (!strcmp(p->declarator->name, "va_alist"));
}
