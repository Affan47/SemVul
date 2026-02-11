createActions()
{
    QAction *a;
    a = aHigh = new QAction(this);
    a->setIcon(theme()->icon(Core::Constants::ICONPRIORITY_HIGH));
    a = aMedium = new QAction(this);
    a->setIcon(theme()->icon(Core::Constants::ICONPRIORITY_MEDIUM));
    a = aLow = new QAction(this);
    a->setIcon(theme()->icon(Core::Constants::ICONPRIORITY_LOW));
    m_PriorityButton->addAction(aHigh);
    m_PriorityButton->addAction(aMedium);
    m_PriorityButton->addAction(aLow);
    m_PriorityButton->setDefaultAction(aMedium);

}
