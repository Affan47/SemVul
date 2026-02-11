setToolBox(AbstractToolBox *toolBox)
{
    if (d->toolBox.data()) {
        d->toolBox.data()->deleteLater();
    }
    d->toolBox = toolBox;
}
