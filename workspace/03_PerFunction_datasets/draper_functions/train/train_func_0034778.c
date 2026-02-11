syntaxCopy()
{
    DebugStatement *s = new DebugStatement(loc,
                statement ? statement->syntaxCopy() : NULL);
    return s;
}
