overridingComment() const
{
    if (d->cui)
        return d->cui->overridingComment->toPlainText();
    return QString::null;
}
