DoHeal(Battle * b)
{

	for(int i = 5; i > 0; --i)
		DoHealLevel(b, i, 0);

	DoHealLevel(b, 1, 1);
}
