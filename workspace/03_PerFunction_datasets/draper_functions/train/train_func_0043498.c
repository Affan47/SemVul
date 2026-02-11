createHeaderFrame (const QString & url1, const QString & urlText1, const QString & url2, const QString & urlText2, const QString & inactiveColor, const QString & activeColor,
                                         QLabel * & label1, QLabel * & label2){
    QFrame * titleFrame = new QFrame();
    titleFrame->setObjectName("wsSwitchableFrameHeader");

    QHBoxLayout * titleFrameLayout = new QHBoxLayout;
    zeroMargin(titleFrameLayout);

    label1 = new QLabel(makeUrlText(url1, urlText1, inactiveColor));
    label1->setObjectName("headerTitle1");
    titleFrameLayout->addWidget(label1);
    connect(label1, SIGNAL(linkActivated(const QString &)), this, SLOT(clickBlog(const QString &)));

    QLabel * titleSpace = new QLabel(tr("|"));
    titleSpace->setObjectName("headerTitleSpace");
    titleFrameLayout->addWidget(titleSpace);

    label2 = new QLabel(makeUrlText(url2, urlText2, activeColor));
    label2->setObjectName("headerTitle2");
    titleFrameLayout->addWidget(label2);
    connect(label2, SIGNAL(linkActivated(const QString &)), this, SLOT(clickBlog(const QString &)));

    titleFrameLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    titleFrame->setLayout(titleFrameLayout);

    return titleFrame;
}
