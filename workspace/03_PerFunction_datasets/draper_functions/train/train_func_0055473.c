CheckDepend(int lev, SkillDepend &dep)
{
	AString skname = dep.skill;
	int sk = LookupSkill(&skname);
	if (sk == -1) return 0;
	int temp = GetRealSkill(sk);
	if(temp < dep.level) return 0;
	if(lev >= temp) return 0;
	return 1;
}
