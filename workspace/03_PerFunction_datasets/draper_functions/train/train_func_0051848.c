deleteNext(unsigned long index)
{
    while (_next && index--) {
        Token *n = _next;
        _next = n->next();
        delete n;
    }

    if (_next)
        _next->previous(this);
    else if (tokensBack)
        *tokensBack = this;
}
