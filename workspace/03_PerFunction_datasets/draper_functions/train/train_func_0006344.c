setupUi(QDialog *DatePickerDialog)
{
    if (DatePickerDialog->objectName().isEmpty())
        DatePickerDialog->setObjectName(QString::fromUtf8("DatePickerDialog"));
    DatePickerDialog->setWindowModality(Qt::WindowModal);
    DatePickerDialog->setAcceptDrops(false);
    DatePickerDialog->setModal(true);

    QGridLayout *mainGrid = new QGridLayout(this);
    lblOccur = new QLabel("When did this ride occur?", this);
    mainGrid->addWidget(lblOccur, 0,0);
    dateTimeEdit = new QDateTimeEdit(this);


	QDateTime *dt = new QDateTime;
	date = dt->currentDateTime();
	dateTimeEdit->setDateTime(date);

    mainGrid->addWidget(dateTimeEdit,0,1);
    lblBrowse = new QLabel("Choose a CSV file to upload", this);
    mainGrid->addWidget(lblBrowse, 1,0);
    btnBrowse = new QPushButton(this);
    mainGrid->addWidget(btnBrowse,2,0);
    txtBrowse = new QLineEdit(this);
    mainGrid->addWidget(txtBrowse,2,1);

    btnOK = new QPushButton(this);
    mainGrid->addWidget(btnOK, 3,0);
    btnCancel = new QPushButton(this);
    mainGrid->addWidget(btnCancel, 3,1);

    DatePickerDialog->setWindowTitle(
        QApplication::translate("DatePickerDialog", "Import CSV file", 0,
                                QApplication::UnicodeUTF8));

    btnBrowse->setText(
        QApplication::translate("DatePickerDialog", "File to import...", 0,
                                QApplication::UnicodeUTF8));
    btnOK->setText(
        QApplication::translate("DatePickerDialog", "OK", 0,
                                QApplication::UnicodeUTF8));
    btnCancel->setText(
        QApplication::translate("DatePickerDialog", "Cancel", 0,
                                QApplication::UnicodeUTF8));

    connect(btnOK, SIGNAL(clicked()), this, SLOT(on_btnOK_clicked()));
    connect(btnBrowse, SIGNAL(clicked()), this, SLOT(on_btnBrowse_clicked()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(on_btnCancel_clicked()));


	dateTimeEdit->setEnabled(FALSE);
	lblOccur->setEnabled(FALSE);
	btnOK->setEnabled(FALSE);

    Q_UNUSED(DatePickerDialog);
}
