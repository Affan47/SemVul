TemplateReport()
{

	AString temp;
	temp = *name;

	if (guard == GUARD_GUARD) temp += ", on guard";
	if (guard == GUARD_AVOID) temp += ", avoiding";
	if (GetFlag(FLAG_BEHIND)) temp += ", behind";
	if (reveal == REVEAL_UNIT) temp += ", revealing unit";
	if (reveal == REVEAL_FACTION) temp += ", revealing faction";
	if (GetFlag(FLAG_HOLDING)) temp += ", holding";
	if (GetFlag(FLAG_AUTOTAX)) temp += ", taxing";
	if (GetFlag(FLAG_NOAID)) temp += ", receiving no aid";
	if (GetFlag(FLAG_SHARING)) temp += ", sharing";
	if (GetFlag(FLAG_CONSUMING_UNIT)) temp += ", consuming unit's food";
	if (GetFlag(FLAG_CONSUMING_FACTION)) temp += ", consuming faction's food";
	if (GetFlag(FLAG_NOCROSS_WATER)) temp += ", won't cross water";
	temp += SpoilsReport();

	temp += items.Report(2, 1, 0);
	temp += ". Weight: ";
	temp += AString(items.Weight());
	temp += ". Capacity: ";
	temp += AString(FlyingCapacity());
	temp += "/";
	temp += AString(RidingCapacity());
	temp += "/";
	temp += AString(WalkingCapacity());
	temp += "/";
	temp += AString(SwimmingCapacity());
	temp += ". Skills: ";
	temp += skills.Report(GetMen());

	if (type == U_MAGE || type == U_GUARDMAGE) {
		temp += MageReport();
	}
	temp += ReadyItem();
	temp += StudyableSkills();

	if (describe) {
		temp += AString("; ") + *describe;
	}
	temp += ".";
	return temp;
}
