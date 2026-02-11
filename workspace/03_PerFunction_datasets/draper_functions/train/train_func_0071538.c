CanStudy(int sk)
{
	if(skills.GetStudyRate(sk, GetMen()) < 0) return 0;

	int curlev = GetRealSkill(sk);

	if(SkillDefs[sk].flags & SkillType::DISABLED) return 0;

	unsigned int c;
	for(c = 0; c < sizeof(SkillDefs[sk].depends)/sizeof(SkillDepend); c++) {
		if(SkillDefs[sk].depends[c].skill == NULL) return 1;
		SkillType *pS = FindSkill(SkillDefs[sk].depends[c].skill);
		if (pS && (pS->flags & SkillType::DISABLED)) continue;
		if(!CheckDepend(curlev, SkillDefs[sk].depends[c])) return 0;
	}
	return 1;
}
