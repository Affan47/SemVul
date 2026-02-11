SetErrorFunction(Deque *l,ErrorFunction fn)
{
    ErrorFunction old;
    if (l == NULL) return iError.RaiseError;
    old = l->RaiseError;
    l->RaiseError = (fn) ? fn : iError.EmptyErrorFunction;
    return old;
}
