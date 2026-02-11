setGroup(QString s)
{
    TraceCostItem* ci = _functionSelection->group(s);
    if (!ci)
	return false;

    return setGroup(ci);
}
