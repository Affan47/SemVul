addChild(RenderLayer *child, RenderLayer* beforeChild)
{
    RenderLayer* prevSibling = beforeChild ? beforeChild->previousSibling() : lastChild();
    if (prevSibling) {
        child->setPreviousSibling(prevSibling);
        prevSibling->setNextSibling(child);
    }
    else
        setFirstChild(child);

    if (beforeChild) {
        beforeChild->setPreviousSibling(child);
        child->setNextSibling(beforeChild);
    }
    else
        setLastChild(child);

    child->setParent(this);

    if (child->isOverflowOnly())
        dirtyOverflowList();
    else {


        RenderLayer* stackingContext = child->stackingContext();
        if (stackingContext)
            stackingContext->dirtyZOrderLists();
    }
    child->updateVisibilityStatus();
    if (child->m_hasVisibleContent || child->m_hasVisibleDescendant)
        childVisibilityChanged(true);
}
