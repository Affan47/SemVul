FcRuleCreate (FcRuleType type,
	      void       *p)
{
    FcRule *r = (FcRule *) malloc (sizeof (FcRule));

    if (!r)
	return NULL;

    r->next = NULL;
    r->type = type;
    switch (type)
    {
    case FcRuleTest:
	r->u.test = (FcTest *) p;
	break;
    case FcRuleEdit:
	r->u.edit = (FcEdit *) p;
	break;
    default:
	free (r);
	r = NULL;
	break;
    }

    return r;
}
