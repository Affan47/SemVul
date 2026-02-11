kind()
{
    return (onemember && onemember->isAggregateDeclaration())
                ? onemember->kind()
                : (char *)"template";
}
