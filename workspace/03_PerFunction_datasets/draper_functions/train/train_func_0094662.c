event(QEvent *e)
{

    if (e->type() == QEvent::Leave || e->type() == QEvent::Enter) repaint();
    return QWidget::event(e);
}
