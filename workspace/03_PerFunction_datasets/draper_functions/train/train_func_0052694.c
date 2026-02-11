isDotOpDispatch(Expression *e)
{
    return e->op == TOKdotti &&
           ((DotTemplateInstanceExp *)e)->ti->name == Id::opDispatch;
}
