syntaxCopy()
{

    SwitchStatement *s = new SwitchStatement(loc,
        condition->syntaxCopy(), body->syntaxCopy(), isFinal);
    return s;
}
