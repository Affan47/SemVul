appendChildNode(RenderObject* newChild)
{
    KHTMLAssert(newChild->parent() == 0);

    newChild->setParent(this);
    RenderObject* lChild = lastChild();

    if(lChild)
    {
        newChild->setPreviousSibling(lChild);
        lChild->setNextSibling(newChild);
    }
    else
        setFirstChild(newChild);

    setLastChild(newChild);


    RenderLayer* layer = 0;
    if (newChild->firstChild() || newChild->layer()) {
        layer = enclosingLayer();
        newChild->addLayers(layer, newChild);

        if (newChild->style()&& (newChild->style()->hasFixedBackgroundImage() || newChild->style()->position() == PFIXED)) {
            if (newChild->style()->hasFixedBackgroundImage())
                canvas()->addStaticObject( newChild );
            if (newChild->style()->position() == PFIXED)
                canvas()->addStaticObject( newChild, true );
        }
    }


    if (style()->visibility() != VISIBLE && newChild->style()->visibility() == VISIBLE && !newChild->layer()) {
        if (!layer) {
            layer = enclosingLayer();
        }
        if (layer) {
            layer->setHasVisibleContent(true);
        }
    }

    if (!newChild->isFloatingOrPositioned() && childrenInline())
        dirtyLinesFromChangedChild(newChild);

    newChild->setNeedsLayoutAndMinMaxRecalc();

    if (!normalChildNeedsLayout()) {

        if (newChild->firstChild() || newChild->isPosWithStaticDim() || !newChild->isPositioned())
            setChildNeedsLayout(true);
        else {
            assert(!newChild->inPosObjectList());
            newChild->containingBlock()->insertPositionedObject(newChild);
        }
    }
}
