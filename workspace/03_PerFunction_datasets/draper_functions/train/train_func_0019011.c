checkPICSratingSafeSurf(String r)
{
	checkPICSagainstoption(r, "000 ", (*o.fg[filtergroup]).pics_safesurf_agerange, "Safesurf age range");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "001 ", (*o.fg[filtergroup]).pics_safesurf_profanity, "Safesurf profanity");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "002 ", (*o.fg[filtergroup]).pics_safesurf_heterosexualthemes, "Safesurf heterosexualthemes");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "003 ", (*o.fg[filtergroup]).pics_safesurf_homosexualthemes, "Safesurf ");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "004 ", (*o.fg[filtergroup]).pics_safesurf_nudity, "Safesurf nudity");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "005 ", (*o.fg[filtergroup]).pics_safesurf_violence, "Safesurf violence");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "006 ", (*o.fg[filtergroup]).pics_safesurf_sexviolenceandprofanity, "Safesurf sexviolenceandprofanity");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "007 ", (*o.fg[filtergroup]).pics_safesurf_intolerance, "Safesurf intolerance");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "008 ", (*o.fg[filtergroup]).pics_safesurf_druguse, "Safesurf druguse");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "009 ", (*o.fg[filtergroup]).pics_safesurf_otheradultthemes, "Safesurf otheradultthemes");
	if (isItNaughty) {
		return;
	}
	checkPICSagainstoption(r, "00A ", (*o.fg[filtergroup]).pics_safesurf_gambling, "Safesurf gambling");
	if (isItNaughty) {
		return;
	}
}
