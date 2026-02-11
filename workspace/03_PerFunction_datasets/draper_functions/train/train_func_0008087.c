callAsFunction(ExecState* exec, JSObject* thisObj, const List& args)
{
    KJS_CHECK_THIS(XPathResult, thisObj);

    khtml::XPathResultImpl* imp = static_cast<XPathResult*>(thisObj)->impl();
    DOMExceptionTranslator exception(exec);

    switch (id) {
    case XPathResult::IterateNext:
        return getDOMNode(exec, imp->iterateNext(exception));
    case XPathResult::SnapshotItem:
        return getDOMNode(exec, imp->snapshotItem(args[0]->toInt32(exec), exception));
    }

    return jsUndefined();
}
