getValueProperty(ExecState* exec, int token) const
{
    kDebug(6070) << token;
    DOMExceptionTranslator exception(exec);
    DOM::Selection sel = currentSelection();

    switch (token) {
        case DOMSelection::AnchorNode:
            return sel.notEmpty() ? getDOMNode(exec, sel.base().node()) : jsNull();
        case DOMSelection::AnchorOffset:
            return jsNumber(sel.notEmpty() ? sel.base().offset() : 0L);
        case DOMSelection::FocusNode:
            return sel.notEmpty() ? getDOMNode(exec, sel.extent().node()) : jsNull();
        case DOMSelection::FocusOffset:
            return jsNumber(sel.notEmpty() ? sel.extent().offset() : 0L);
        case DOMSelection::IsCollapsed:
            return jsBoolean(sel.isCollapsed() || sel.isEmpty());
        case DOMSelection::RangeCount:
            return sel.notEmpty() ? jsNumber(1) : jsNumber(0);
    }

    assert (false);
    return jsUndefined();
}
