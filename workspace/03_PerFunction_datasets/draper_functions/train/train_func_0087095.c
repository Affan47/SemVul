setupController()
{
    Animator::instance()->restart();
    m_seaView->clear();
    m_chat->hide();


    m_seaView->screen(Sea::Player(0))->fadeOut();
    m_seaView->screen(Sea::Player(1))->fadeOut();

    delete m_controller;
    m_controller = createController();
    m_menu->setupController(m_controller, 0, m_seaView, m_chat, false);
    startGame();
}
