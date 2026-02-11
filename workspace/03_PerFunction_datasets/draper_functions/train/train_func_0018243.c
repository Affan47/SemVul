createChangedMap()
{


	changedMap.insert("QButton", SIGNAL(stateChanged(int)));
	changedMap.insert("QCheckBox", SIGNAL(stateChanged(int)));


	changedMap.insert("QRadioButton",SIGNAL(toggled (bool)));
	changedMap.insert("QComboBox", SIGNAL(activated (int)));

	changedMap.insert("QDateEdit", SIGNAL(valueChanged(const QDate &)));
	changedMap.insert("QDateTimeEdit", SIGNAL(valueChanged(const QDateTime &)));
	changedMap.insert("QDial", SIGNAL(valueChanged (int)));
	changedMap.insert("QLineEdit", SIGNAL(textChanged(const QString &)));
	changedMap.insert("QSlider", SIGNAL(valueChanged(int)));
	changedMap.insert("QSpinBox", SIGNAL(valueChanged(int)));
	changedMap.insert("QTimeEdit", SIGNAL(valueChanged(const QTime &)));
	changedMap.insert("QTextEdit", SIGNAL(textChanged()));
	changedMap.insert("QTextBrowser", SIGNAL(sourceChanged(const QString &)));
	changedMap.insert("QMultiLineEdit", SIGNAL(textChanged()));


}
