updateLayerPosition()
{


    if (renderer()->isCanvas())
        return;

    int x = m_object->xPos();
    int y = m_object->yPos() - m_object->borderTopExtra();

    if (!m_object->isPositioned()) {


        RenderObject* curr = m_object->parent();
        while (curr && !curr->layer()) {
            x += curr->xPos();
            y += curr->yPos();
            curr = curr->parent();
        }
	if (curr)
	  y += curr->borderTopExtra();
    }

    if (m_object->isRelPositioned())
        static_cast<RenderBox*>(m_object)->relativePositionOffset(x, y);


    if (m_object->isPositioned() && enclosingPositionedAncestor()) {
        RenderLayer* positionedParent = enclosingPositionedAncestor();


        positionedParent->subtractScrollOffset(x, y);
        positionedParent->checkInlineRelOffset(m_object, x, y);
    }
    else if (parent())
        parent()->subtractScrollOffset(x, y);

    setPos(x,y);
}
