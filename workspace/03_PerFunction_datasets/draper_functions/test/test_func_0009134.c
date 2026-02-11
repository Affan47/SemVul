getClass(getclassfn initializeClass) const
{
    jclass cls = (*initializeClass)(true);

    if (cls == NULL)
    {
        lock locked;
        cls = (*initializeClass)(false);
    }

    return cls;
}
