isGroupExpanded(Form::FormItem *item, bool defaultValue)
{
    if (item->getOptions().contains(EXTRAS_GROUP_EXPANDED, Qt::CaseInsensitive))
        return true;
    return defaultValue;
}
