any_vars(rasqal_triple *t)
{
    if (t->origin && t->origin->type == RASQAL_LITERAL_VARIABLE) {
        return 1;
    }
    if (t->subject->type == RASQAL_LITERAL_VARIABLE) {
        return 1;
    }
    if (t->predicate->type == RASQAL_LITERAL_VARIABLE) {
        return 1;
    }
    if (t->object->type == RASQAL_LITERAL_VARIABLE) {
        return 1;
    }

    return 0;
}
