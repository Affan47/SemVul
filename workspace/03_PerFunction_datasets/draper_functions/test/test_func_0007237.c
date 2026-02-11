setUpSlowDNAWeightMat()
{
    slowDNAMatGroup = new QGroupBox(tr("DNA Weight Matrix"));
    slowDNAWeightMat = new QButtonGroup;
    slowDNAWeightMat->setExclusive(true);
    slowDNAIUB = new QRadioButton("IUB");
    slowDNAClustalw = new QRadioButton("CLUSTALW(1.6)");
    slowDNAUser = new QRadioButton("User defined");
    connect(slowDNAUser, SIGNAL(clicked()), this, SLOT(userDNAClicked()));

    slowDNAWeightMat->addButton(slowDNAIUB);
    slowDNAWeightMat->addButton(slowDNAClustalw);
    slowDNAWeightMat->addButton(slowDNAUser);

    dnaMatLayout = new QGridLayout;
    dnaMatLayout->addWidget(slowDNAIUB, 0, 0);
    dnaMatLayout->addWidget(slowDNAClustalw, 0, 1);
    dnaMatLayout->addWidget(slowDNAUser, 0, 2);
    slowDNAMatGroup->setLayout(dnaMatLayout);
}
