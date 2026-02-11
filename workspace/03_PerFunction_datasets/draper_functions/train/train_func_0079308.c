bc_eq(BooleanClause *self, BooleanClause *o)
{
    return ((self->occur == o->occur) && q_eq(self->query, o->query));
}
