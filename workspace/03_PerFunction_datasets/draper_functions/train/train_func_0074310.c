setFocus()
{
    if (isUrlEditable()) {
        d->m_pathBox->setFocus();
    } else {
        QWidget::setFocus();
    }
}
