createTodayButton()
{
    QToolButton *button = new QToolButton(this);
    QString icon = theme()->iconFileName(CalendarTheme::NavigationBookmarks);
    if (icon.isEmpty())
        button->setText("^");
    else
        button->setIcon(QIcon(icon));

    QMenu *menu = new QMenu(this);
    aToday = menu->addAction(tkTr(Trans::Constants::TODAY), this, SLOT(todayPage()));
    aTomorrow = menu->addAction(tkTr(Trans::Constants::TOMORROW), this, SLOT(tomorrowPage()));
    aYesterday = menu->addAction(tkTr(Trans::Constants::YESTERDAY), this, SLOT(yesterdayPage()));
    menu->addSeparator();
    aCurrentWeek = menu->addAction(tkTr(Trans::Constants::CURRENT_WEEK), this, SLOT(currentWeekPage()));
    aNextWeek = menu->addAction(tkTr(Trans::Constants::NEXT_WEEK), this, SLOT(nextWeekPage()));
    menu->addSeparator();
    aCurrentMonth = menu->addAction(tkTr(Trans::Constants::CURRENT_MONTH), this, SLOT(currentMonthPage()));
    aNextMonth = menu->addAction(tkTr(Trans::Constants::NEXT_MONTH), this, SLOT(nextMonthPage()));
    menu->addSeparator();

    mViewRange = menu->addMenu(tr("View range"));
    for(int i = 1; i < 19; ++i) {
        QAction *action = mViewRange->addAction(QString("%1 %2").arg(i*5).arg(tkTr(Trans::Constants::MINUTES)));
        action->setData(i);
    }
    connect(mViewRange, SIGNAL(triggered(QAction*)), this, SLOT(changeGranularity(QAction*)));

    button->setMenu(menu);
    button->setPopupMode(QToolButton::InstantPopup);

    return button;
}
