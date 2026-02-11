Readin(Ainfile *s, AList *facs, ATL_VER v)
{
	name = s->GetStr();
	describe = s->GetStr();
	if (*describe == "none") {
		delete describe;
		describe = 0;
	}
	num = s->GetInt();
	type = s->GetInt();
	int i = s->GetInt();
	faction = GetFaction(facs, i);
	guard = s->GetInt();
	if(guard == GUARD_ADVANCE) guard = GUARD_NONE;
	if(guard == GUARD_SET) guard = GUARD_GUARD;
	reveal = s->GetInt();


	free = 0;
	readyItem = -1;
	for(i = 0; i < MAX_READY; i++) {
		readyWeapon[i] = -1;
		readyArmor[i] = -1;
	}

	free = s->GetInt();
	AString *temp;
	temp = s->GetStr();
	readyItem = LookupItem(temp);
	delete temp;
	for(i = 0; i < MAX_READY; i++) {
		temp = s->GetStr();
		readyWeapon[i] = LookupItem(temp);
		delete temp;
		temp = s->GetStr();
		readyArmor[i] = LookupItem(temp);
		delete temp;
	}
	flags = s->GetInt();

	items.Readin(s);
	skills.Readin(s);
	temp = s->GetStr();
	combat = LookupSkill(temp);
	delete temp;
}
