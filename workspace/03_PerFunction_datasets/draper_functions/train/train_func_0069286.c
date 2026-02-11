shortcut() const
{
    KShortcut ret;
    ret.setPrimary(d->ui.priEditor->keySequence());
    ret.setAlternate(d->ui.altEditor->keySequence());
    return ret;
}
