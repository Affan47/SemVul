qHash(const KParts::ScriptableExtension::FunctionRef& f)
{
    return qHash(qMakePair(f.base, f.field));
}

}
