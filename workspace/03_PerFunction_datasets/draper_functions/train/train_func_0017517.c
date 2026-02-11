GetTokenKindString() const
{
    switch (m_TokenKind)
    {
        case tkClass:        return _T("class");
        case tkNamespace:    return _T("namespace");
        case tkTypedef:      return _T("typedef");
        case tkEnum:         return _T("enum");
        case tkEnumerator:   return _T("enumerator");
        case tkFunction:     return _T("function");
        case tkConstructor:  return _T("constructor");
        case tkDestructor:   return _T("destructor");
        case tkPreprocessor: return _T("preprocessor");
        case tkMacro:        return _T("macro");
        case tkVariable:     return _T("variable");
        case tkAnyContainer: return _T("any container");
        case tkAnyFunction:  return _T("any function");
        case tkUndefined:    return _T("undefined");
        default:             return wxEmptyString;
    }
}
