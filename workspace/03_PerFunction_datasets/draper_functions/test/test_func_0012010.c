wheelEvent( QWheelEvent *e )
{
    if (horizontalScrollBar() && (arrangement() == Q3IconView::TopToBottom)) {
        QWheelEvent ce(e->pos(), e->delta(), e->buttons(), e->modifiers(), Qt::Horizontal);
        QApplication::sendEvent( horizontalScrollBar(), &ce);
	if (ce.isAccepted()) {
            e->accept();
	    return;
	}
    }
    Q3IconView::wheelEvent(e);
}
