GetArmor(AString &itm, int ass)
{
	int item = LookupItem(&itm);
	ArmorType *pa = FindArmor(itm.Str());

	if (pa == NULL) return -1;
	if (ass && !(pa->flags & ArmorType::USEINASSASSINATE)) return -1;

	int num = items.GetNum(item);
	if (num < 1) return -1;

	if (!(ItemDefs[item].type & IT_ARMOR)) return -1;
	items.SetNum(item, num - 1);
	return item;
}
