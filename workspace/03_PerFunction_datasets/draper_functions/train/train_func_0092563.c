setUpSlowProteinWeightMat()
{
    slowProtMatGroup = new QGroupBox(tr("Protein Weight Matrix"));
    slowProteinWeightMat = new QButtonGroup;
    slowProteinWeightMat->setExclusive(true);
    slowProtBlosum30 = new QRadioButton("BLOSUM 30");
    slowProtPAM350 = new QRadioButton("PAM 350");
    slowProtGonnet250 = new QRadioButton("Gonnet 250");
    slowProtIdentity = new QRadioButton("Identity matrix");
    slowProtAAUserMat = new QRadioButton("User defined");

    connect(slowProtAAUserMat, SIGNAL(clicked()), this, SLOT(userProteinClicked()));

    slowProteinWeightMat->addButton(slowProtBlosum30);
    slowProteinWeightMat->addButton(slowProtPAM350);
    slowProteinWeightMat->addButton(slowProtGonnet250);
    slowProteinWeightMat->addButton(slowProtIdentity);
    slowProteinWeightMat->addButton(slowProtAAUserMat);

    protMatLayout = new QGridLayout;
    protMatLayout->addWidget(slowProtBlosum30, 0, 0);
    protMatLayout->addWidget(slowProtPAM350, 0, 1);
    protMatLayout->addWidget(slowProtGonnet250, 0, 2);
    protMatLayout->addWidget(slowProtIdentity, 1, 0);
    protMatLayout->addWidget(slowProtAAUserMat, 1, 1);
    slowProtMatGroup->setLayout(protMatLayout);
}
