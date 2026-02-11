isAncestor( NodeImpl *other ) const
{

    const NodeImpl *n;
    for (n = this; n; n = n->parentNode()) {
        if (n == other)
            return true;
    }
    return false;
}
