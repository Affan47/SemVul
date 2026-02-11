setParent(QWidget *newParent)
{
    if (parent()) {
        parent()->removeEventFilter(this);
    }
    QWidget::setParent(newParent);
    if (newParent) {
        newParent->installEventFilter(this);
    }
}
