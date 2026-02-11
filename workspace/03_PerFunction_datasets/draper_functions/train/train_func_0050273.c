showAsDialog(const QString& caption)
{
    if (!isVisible())
    {
        new PlayerSelector::Dialog(this, caption);
    }
}
