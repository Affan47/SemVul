setAppropriate (const QString& name, bool appropriate)
{
    if (!d->items.contains(name))
        return;

    KAssistantDialog::setAppropriate(d->items[name],appropriate);
}
