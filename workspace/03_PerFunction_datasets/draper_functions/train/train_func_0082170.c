syntaxCopy()
{
    return new CallExp(loc, e1->syntaxCopy(), arraySyntaxCopy(arguments));
}
