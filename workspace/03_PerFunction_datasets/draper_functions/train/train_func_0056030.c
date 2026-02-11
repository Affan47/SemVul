at(const QtSoapQName &key)
{
    static QtSoapType NIL;

    QListIterator<QtSmartPtr<QtSoapType> > it(dict);
    while (it.hasNext()) {
        QtSoapType *ret = it.next().ptr();
        if (ret->name() == key)
            return *ret;
    }

    return NIL;
}
