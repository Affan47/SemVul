Writeout(Aoutfile *f)
{
	AString temp;

	if (type != -1) {
		if(Globals->REQUIRED_EXPERIENCE) {
			temp = AString(SkillDefs[type].abbr) + " " + days + " " + exp;
		} else {
			temp = AString(SkillDefs[type].abbr) + " " + days;
		}
	} else {
		if(Globals->REQUIRED_EXPERIENCE) {
			temp = AString("NO_SKILL 0 0");
		} else {
			temp = AString("NO_SKILL 0");
		}
	}
	f->PutStr(temp);
}
