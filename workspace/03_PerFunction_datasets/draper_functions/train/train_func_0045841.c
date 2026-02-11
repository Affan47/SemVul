createNavigationButtons()
{
    QWidget *w = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(w);
    layout->setSpacing(0);
    layout->setMargin(0);


    m_previousPageButton = new QToolButton(this);
    QString icon = theme()->iconFileName(CalendarTheme::NavigationPrevious);
    if (icon.isEmpty())
        m_previousPageButton->setText("<<");
    else
        m_previousPageButton->setIcon(QIcon(icon));

    m_nextPageButton = new QToolButton(this);
    icon = theme()->iconFileName(CalendarTheme::NavigationNext);
    if (icon.isEmpty())
        m_nextPageButton->setText(">>");
    else
        m_nextPageButton->setIcon(QIcon(icon));

    layout->addWidget(m_previousPageButton);
    layout->addWidget(m_nextPageButton);


    layout->addWidget(m_todayButton = createTodayButton());
    w->setLayout(layout);
    return w;
}
