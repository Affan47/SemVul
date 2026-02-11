isCtfeComparable(Expression *e)
{
    Expression *x = e;
    if (x->op == TOKslice)
        x = ((SliceExp *)e)->e1;

    if (x->isConst() != 1 &&
        x->op != TOKnull &&
        x->op != TOKstring &&
        x->op != TOKfunction &&
        x->op != TOKdelegate &&
        x->op != TOKarrayliteral &&
        x->op != TOKstructliteral &&
        x->op != TOKclassreference)
    {
        return false;
    }
    return true;
}
