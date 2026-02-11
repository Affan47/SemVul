findNamespace(const Token * tok, const Scope * scope) const
{
    const Scope * s = findScope(tok, scope);

    if (s)
        return s;
    else if (scope->nestedIn)
        return findNamespace(tok, scope->nestedIn);

    return 0;
}
