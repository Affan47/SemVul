cmp_object_trait(int bonus, random_value base)
{
	int amt = randcalc(base, 0, MINIMISE);
	if (amt > 0) amt = 0;
	return CMP(bonus, amt);
}
