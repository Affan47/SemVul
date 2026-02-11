GetAvailSkill(int sk)
{
	AString str;
	int retval = GetRealSkill(sk);

	forlist (&items) {
		Item *i = (Item *)elem;
		if (ItemDefs[i->type].flags & ItemType::DISABLED) continue;
		if ((SkillDefs[sk].flags & SkillType::MAGIC)
				&& !(type != U_MAGE && type != U_APPRENTICE))
			continue;
		if (i->num < GetMen())
			continue;
		str = ItemDefs[i->type].grantSkill;
		if (ItemDefs[i->type].grantSkill && LookupSkill(&str) == sk) {
			int grant = 0;
			for (unsigned j = 0; j < sizeof(ItemDefs[0].fromSkills)
								 / sizeof(ItemDefs[0].fromSkills[0]); j++) {
				if (ItemDefs[i->type].fromSkills[j]) {
					int fromSkill;

					str = ItemDefs[i->type].fromSkills[j];

					fromSkill = LookupSkill(&str);
					if (fromSkill != -1) {


						if (grant < GetRealSkill(fromSkill))
							grant = GetRealSkill(fromSkill);
					}
				}
			}
			if (grant < ItemDefs[i->type].minGrant)
				grant = ItemDefs[i->type].minGrant;
			if (grant > ItemDefs[i->type].maxGrant)
				grant = ItemDefs[i->type].maxGrant;

			if (grant > retval)
				retval = grant;
		}
	}

	return retval;
}
