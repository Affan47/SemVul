firstLeafChild()
{
    InlineBox *box = firstChild();
    while (box) {
        InlineBox* next = 0;
        if (!box->isInlineFlowBox())
            break;
        next = static_cast<InlineFlowBox*>(box)->firstChild();
        if (!next)
            break;
        box = next;
    }
    return box;
}
