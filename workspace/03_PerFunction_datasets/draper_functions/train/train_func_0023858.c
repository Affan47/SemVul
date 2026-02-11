designMode() const
{
    return part() ? part()->isEditable() : false;
}
