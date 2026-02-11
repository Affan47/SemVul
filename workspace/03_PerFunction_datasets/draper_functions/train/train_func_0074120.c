getNumberOfColumns(Form::FormItem *item, int defaultValue)
{
    if (!item->extraData().value(EXTRAS_KEY_COLUMN).isEmpty())
        return item->extraData().value(EXTRAS_KEY_COLUMN).toInt();
    else
        return defaultValue;
}
