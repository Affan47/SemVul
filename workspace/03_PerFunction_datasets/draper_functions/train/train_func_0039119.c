help()
{
	QString s;

	s+=tr("Abbreviations in this dialog:");
	s+="\n\n";
	s+=tr("'Students' (the text near the spin box), means 'Number of students (-1 for automatic)'");
	s+="\n";
	s+=tr("'Split' means 'Split into ... activities per week'");
	s+="\n";
	s+=tr("'Min days' means 'The minimum required distance in days between each pair of activities'");
	s+="\n";
	s+=tr("'Weight %' means 'Percentage of added constraint (min days between activities constraint). Recommended: 95.0%-100.0%'");
	s+="\n";
	s+=tr("'Consecutive' means 'If activities on same day, force consecutive?'");
	s+="\n";
	s+=tr("The 'Duration' spin box and the 'Active' check box refer to each component of current activity, you can change "
	 "them for each component, separately, by selecting the corresponding tab in the tab widget.");
	s+="\n\n";

	s+=tr("A first notice: "
	 "If you use a 5 days week: "
	 "when adding an activity split into only 2 components "
	 "per week, the best practice is to add min days between activities to be 2. "
	 "If you split an activity into 3 components per week - please read FAQ question Q1-5-September-2008");
	s+="\n\n";

	s+=tr("You can select a teacher from all the teachers with the mouse or with the keyboard tab/up/down, then "
	 "double click it to add it to the selected teachers for current activity. "
	 "You can then choose to remove a teacher from the selected teachers. You can highlight it "
	 "with the mouse or with the keyboard, then double click it to remove this teacher from the selected teachers.");

	s+="\n\n";

	s+=tr("The same procedure (double click) applies to students sets and activity tags.");

	s+="\n\n";

	s+=tr("You can check/uncheck show years, show groups or show subgroups.");
	s+="\n\n";

	 s+=tr("If you split a larger activity into more activities per week, you have a multitude of choices:\n"
	 "You can choose the minimum distance in days between each pair of activities."
	 " Please note that a minimum distance of 1 means that the activities must not be in the same day, "
	 "a minimum distance of 2 means that the activities must be separated by one day (distance from Monday"
	 " to Wednesday for instance is 2 days), etc.");

	s+="\n\n";

	 s+=tr("If you have for instance an activity with 2 lessons per week and you want to spread them to at "
	 "least 2 days distance, you can add a constraint min days with min days = 2 and weight 95% "
	 "(or higher). If you want also to ensure that activities will "
	 "be separated by at least one day, you can use this feature: "
	 "add a constraint min days with minimum days 2 and weight 95% or lower, and after that you'll get "
	 "the possibility to add another constraint with min 1 days and weight 95% or higher. "
	 "It works if you first select in the dialog the min days >= 2 and click Add activities. Or you can add manually the constraints "
	 "(difficult this way). "
	 "Important: it is best practice to consider both constraints to have 95% weight. The combination assures that "
	 "the resultant is 99.75% weight");

	s+="\n\n";

	s+=tr("Please note that the min days distance is a time constraint and you can only see/modify it in the "
	 "time constraints dialogs, not in the modify activity dialog. Additionally, you can see the constraints "
	 "for each activity in the details text box of each activity");

	s+="\n\n";

	 s+=tr("If you choose a value greater or equal with 1 for min days, a time constraint min days between activities will be added automatically "
	 "(you can see this constraint in the time constraints list or you can see this constraint in the "
	 "detailed description of the activity). You can select a weight percentage for this constraint. "
	 "If you select 100%, the constraint must be respected all the time. If you select 95%, there is a small chance "
	 "that the timetable will not respect this constraint. Recommended values are 95.0%-100.0% (maybe you could try "
	 "with 95%, then 99.75%, or even 100.0%, but the generation time might be larger). Generally, 99.75% might be a good value. "
	 "Note: if you put a value less than 100% and the constraint is too tough, FET is able to find that this constraint "
	 "is impossible and will break it. 99.75% might be better than 95% but possibly slower. The percentage is subjective "
	 "(if you put 95% you may get 6 soft conflicts and if you put 99.75% you may get 3 soft conflicts). "
	 "Starting with FET-5.3.6, it is possible to change this value for all constraints in one click, in constraint min days"
	 " between activities dialog.");

	s+="\n\n";

	s+=tr("There is another option, if the activities are in the same day, force consecutive activities. You can select "
	 "this option for instance if you have 5 lessons of math in 5 days, and there is no timetable which respects "
	 "fully the days separation. Then, you can set the weight percent of the min days constraint to 95% and "
	 "add consecutive if same day. You will have as results say 3 lessons with duration 1 and a 2 hours lesson in another day. "
	 "Please be careful: if the activities are on the same day, even if the constraint has 0% weight, then the activities are forced to be "
	 "consecutive.");

	s+="\n\n";

	s+=tr("Current algorithm cannot schedule 3 activities in the same day if consecutive is checked, so "
	 "you will get no solution in such extreme cases (for instance, if you have 3 lessons and a teacher which works only 1 day per week, "
	 "and select 'force consecutive if same day', you will get an imposssible timetable. But these are extremely unlikely cases).");

	s+="\n\n";

	s+=tr("Note: You cannot add 'consecutive if same day' with min days=0. If you want this, you have to add "
	 "min days at least 1 (and any weight percentage).");

	s+="\n\n";

	s+=tr("Starting with version 5.0.0, it is possible to add activities with no students or no teachers");

	s+="\n\n";

	s+=tr("If you select a number of min days above 1, you will get the possibility "
	 "to add a second constraint min days between activities, with min days 1 and a percentage of your choice. Just click "
	 "Add activities");


	QDialog dialog(this);

	dialog.setWindowTitle(tr("FET - help on adding activity(ies)"));

	QVBoxLayout* vl=new QVBoxLayout(&dialog);
	QPlainTextEdit* te=new QPlainTextEdit();
	te->setPlainText(s);
	te->setReadOnly(true);
	QPushButton* pb=new QPushButton(tr("OK"));

	QHBoxLayout* hl=new QHBoxLayout(0);
	hl->addStretch(1);
	hl->addWidget(pb);

	vl->addWidget(te);
	vl->addLayout(hl);
	connect(pb, SIGNAL(clicked()), &dialog, SLOT(close()));

	dialog.resize(700,500);
	centerWidgetOnScreen(&dialog);

	setParentAndOtherThings(&dialog, this);
	dialog.exec();
}
