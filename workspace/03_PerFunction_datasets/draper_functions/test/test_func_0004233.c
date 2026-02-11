initMoveMenu ()
{
    moveMenu = new QMenu(this);

    Move1Action = new QAction(i18n("Move 1"), this);
    connect(Move1Action, SIGNAL(triggered()),m_automaton->game(), SLOT(slotInvade1()));

    Move5Action = new QAction(i18n("Move 5"), this);
    connect(Move5Action, SIGNAL(triggered()),m_automaton->game(), SLOT(slotInvade5()));

    Move10Action = new QAction(i18n("Move 10"), this);
    connect(Move10Action, SIGNAL(triggered()),m_automaton->game(), SLOT(slotInvade10()));

    moveMenu->addAction(Move1Action);
    moveMenu->addAction(Move5Action);
    moveMenu->addAction(Move10Action);


}
