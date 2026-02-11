clearFloats()
{
    if (m_floatingObjects) {
        QListIterator<FloatingObject*> it(*m_floatingObjects);
        while ( it.hasNext() )
            delete it.next();
        m_floatingObjects->clear();
    }


    if (flowAroundFloats() || isRoot() || isCanvas() || isFloatingOrPositioned() || isTableCell()) return;

    RenderObject *prev = previousSibling();


    bool parentHasFloats = false;
    while (prev) {
        if (!prev->isRenderBlock() || prev->isFloatingOrPositioned() || prev->flowAroundFloats()) {
            if ( prev->isFloating() && parent()->isRenderBlock() ) {
                parentHasFloats = true;
            }
            prev = prev->previousSibling();
        } else
            break;
    }

    int offset = m_y;
    if (parentHasFloats)
    {
        addOverHangingFloats( static_cast<RenderBlock *>( parent() ),
                              parent()->borderLeft() + parent()->paddingLeft(), offset, false );
    }

    int xoffset = 0;
    if (prev) {
        if(prev->isTableCell()) return;
        offset -= prev->yPos();
    } else {
        prev = parent();
        if(!prev) return;
        xoffset += prev->borderLeft() + prev->paddingLeft();
    }


    if(!prev->isRenderBlock()) return;
    RenderBlock * flow = static_cast<RenderBlock *>(prev);
    if(!flow->m_floatingObjects) return;
    if(flow->floatBottom() > offset)
        addOverHangingFloats( flow, xoffset, offset, false );
}
