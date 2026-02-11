setupUi()
{
	resize(554, 204);
	label = new QLabel(this);
	label->setObjectName(QString::fromUtf8("label"));
	label->setGeometry(QRect(30, 30, 461, 16));
	lineEdit = new QLineEdit(this);
	lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
	lineEdit->setGeometry(QRect(30, 60, 461, 20));
	selOutputButton = new QPushButton(this);
	selOutputButton->setObjectName(QString::fromUtf8("selOutputButton"));
	selOutputButton->setGeometry(QRect(510, 60, 31, 23));
	spinBox = new QSpinBox(this);
	spinBox->setObjectName(QString::fromUtf8("spinBox"));
	spinBox->setGeometry(QRect(30, 120, 42, 22));
	spinBox->setMaximum(9);
	spinBox->setValue(1);
	label_2 = new QLabel(this);
	label_2->setObjectName(QString::fromUtf8("label_2"));
	label_2->setGeometry(QRect(30, 90, 251, 16));
	addButton = new QPushButton(this);
	addButton->setObjectName(QString::fromUtf8("addButton"));
	addButton->setGeometry(QRect(30, 160, 75, 23));
	cancelButton = new QPushButton(this);
	cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
	cancelButton->setGeometry(QRect(460, 160, 75, 23));


	setWindowTitle("Add Output Tape");
	label->setText("Name of output file:");
	selOutputButton->setText("...");
	label_2->setText("Number of blocks to extarct into this tape file:");
	addButton->setText("Add");
	cancelButton->setText("Cancel");
}
