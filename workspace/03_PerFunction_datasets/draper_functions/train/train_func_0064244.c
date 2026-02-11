new_class(Classification *cl)
{
    Class *c = MALLOC(Class);
    c->first = c->last = NULL;
    c->prev_class = NULL;
    c->next_class = cl->first_class;
    if (cl->first_class) cl->first_class->prev_class = c;
    cl->first_class = c;
    return c;
}
