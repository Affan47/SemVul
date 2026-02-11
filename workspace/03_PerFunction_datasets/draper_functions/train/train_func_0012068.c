handleMouseMoveEventSelection(khtml::MouseMoveEvent *event)
{

    if (!d->m_bMousePressed)
        return;

#ifdef KHTML_NO_SELECTION
    if (d->m_doc && d->m_view) {
        QPoint diff( mouse->globalPos() - d->m_dragLastPos );

        if (abs(diff.x()) > 64 || abs(diff.y()) > 64) {
            d->m_view->scrollBy(-diff.x(), -diff.y());
            d->m_dragLastPos = mouse->globalPos();
        }
    }
#else

    QMouseEvent *mouse = event->qmouseEvent();
    DOM::Node innerNode = event->innerNode();

    if ( (mouse->buttons() & Qt::LeftButton) == 0 || !innerNode.handle() || !innerNode.handle()->renderer() ||
        !innerNode.handle()->renderer()->shouldSelect())
            return;


    extendSelectionTo(event->x(), event->y(), innerNode);
#endif
}
