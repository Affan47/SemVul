arrayHasNonConstPointers(Expressions *elems)
{
    for (size_t i = 0; i < elems->dim; i++)
    {   Expression *e = (*elems)[i];
        if (e && hasNonConstPointers(e))
            return true;
    }
    return false;
}
