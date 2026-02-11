help(QWidget* parent)
{
	QString s=tr("Important information about constraints students (set) min hours daily:");

	s+="\n\n";

	s+=tr("Normally, these constraints do not allow empty days for students (and the check boxes in the dialogs are not selectable).");
	s+=" ";
	s+=tr("If you really need this constraint to allow empty days for students, you must enable the option from Settings->Advanced menu and select the check box.");
	s+="\n\n";
	s+=tr("Be very careful: if your school does not allow empty days for students or if a timetable does not exist with empty days for students, you MUST"
		" keep the constraints the usual way, without allowing empty days.");
	s+=" ";
	s+=tr("The reason is performance: speed of generation and the ability of FET to find a solution.");
	s+=" ";
	s+=tr("If you allow empty days to these constraints and a solution exists only with non-empty days, FET might not be able to find it.");
	s+="\n\n";
	s+=tr("For normal schools or high-schools, probably you won't need to enable this option. Maybe for universities you will need to enable this option.");
	s+="\n\n";
	s+=tr("So, remember: don't allow empty days unless you need it.");

	LongTextMessageBox::largeInformation(parent, tr("FET information"), s);
}
