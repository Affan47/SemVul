setGrade(int grade)
{
	double desktop = gDesktop::font()->size();

	if (grade < -4 || grade > 16)
		return;

	setSize(GRADE_TO_SIZE(grade, desktop));
}
