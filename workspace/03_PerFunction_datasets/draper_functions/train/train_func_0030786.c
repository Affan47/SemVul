createToolbar()
{
    QToolBar* tb = new QToolBar(tr("Main Toolbar"), this);
    tb->setObjectName("main-toolbar");
    addToolBar(Qt::TopToolBarArea, tb);

    tb->addAction(_openAction);
    tb->addSeparator();

    tb->addAction(_cyclesToggleAction);
    tb->addAction(_percentageToggleAction);
    tb->addAction(_expandedToggleAction);
    tb->addAction(_hideTemplatesToggleAction);
    tb->addSeparator();

    tb->addAction(_backAction);
    tb->addAction(_forwardAction);
    tb->addAction(_upAction);
    tb->addSeparator();

    tb->addWidget(_eventTypeBox);
}
