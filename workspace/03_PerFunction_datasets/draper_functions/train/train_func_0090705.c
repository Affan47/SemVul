createBlogContentFrame(const QString & url, const QString & urlText, const QString & logoPath, const QString & footerLabelColor) {
    QFrame * uberFrame = new QFrame;
    QVBoxLayout * uberFrameLayout = new QVBoxLayout;
    zeroMargin(uberFrameLayout);

    BlogListWidget * listWidget = new BlogListWidget;
    listWidget->setObjectName("blogList");
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setItemDelegate(new BlogListDelegate(listWidget));
    connect(listWidget, SIGNAL(itemClicked (QListWidgetItem *)), this, SLOT(blogItemClicked(QListWidgetItem *)));

    uberFrameLayout->addWidget(listWidget);

    QFrame * footerFrame = new QFrame();
    footerFrame->setObjectName("blogFooterFrame");

    QHBoxLayout * footerFrameLayout = new QHBoxLayout;
    zeroMargin(footerFrameLayout);
    footerFrameLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));

    QLabel * footerLabel = new QLabel(QString("<a href='%1'  style='font-family:Droid Sans; text-decoration:none; color:%3;'>%2</a>").arg(url).arg(urlText).arg(footerLabelColor));
    footerLabel->setObjectName("blogLogoText");
    footerFrameLayout->addWidget(footerLabel);
    connect(footerLabel, SIGNAL(linkActivated(const QString &)), this, SLOT(clickBlog(const QString &)));

    footerLabel = new QLabel(tr("<a href='%1'><img src='%2' /></a>").arg(url).arg(logoPath));
    footerLabel->setObjectName("blogLogo");
    footerFrameLayout->addWidget(footerLabel);
    connect(footerLabel, SIGNAL(linkActivated(const QString &)), this, SLOT(clickBlog(const QString &)));

    footerFrame->setLayout(footerFrameLayout);

    uberFrameLayout->addWidget(footerFrame);
    uberFrame->setLayout(uberFrameLayout);

    return listWidget;
}
