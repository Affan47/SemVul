enableButton(ButtonCode button, bool enable)
{
    QAbstractButton *b=getButton(button);
    if (b) {
        b->setEnabled(enable);
    }
}
