setInlinePreviewShown(bool show)
{
    if (d->native) {
        return;
    }
    d->w->setInlinePreviewShown(show);
}
