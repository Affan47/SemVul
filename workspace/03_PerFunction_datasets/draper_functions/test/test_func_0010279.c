syntaxCopy()
{
    return new ExpInitializer(loc, exp->syntaxCopy());
}
