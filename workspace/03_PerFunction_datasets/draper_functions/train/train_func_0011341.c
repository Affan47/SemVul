tokenTestingValue(const QString &name)
{
    Core::IToken *t = token(name);
    if (!t)
        return QVariant();
    return t->testValue();
}
