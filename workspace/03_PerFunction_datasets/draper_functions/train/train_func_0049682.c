checkDeprecated(Loc loc, Scope *sc)
{
    Type::checkDeprecated(loc, sc);
    if (next)
        next->checkDeprecated(loc, sc);
}
