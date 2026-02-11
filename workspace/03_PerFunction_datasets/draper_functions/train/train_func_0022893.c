createActions()
{
   m_pActions->insert(DISC, new QAction(tr("&Disconnect"), this));
   m_pActions->insert(EDIT, new QAction(tr("&Edit Connections ..."), this));
   m_pActions->insert(INFO, new QAction(tr("Connection &Information"), this));
   m_pActions->insert(ABOUT, new QAction(tr("&About"), this));
   m_pActions->insert(QUIT, new QAction(tr("&Quit"), this));

   connect(action(DISC), SIGNAL(triggered()), SLOT(vpnDisconnect()));
   connect(action(EDIT), SIGNAL(triggered()), SLOT(editConnections()));
   connect(action(INFO), SIGNAL(triggered()), SLOT(showConnectionInformation()));
   connect(action(ABOUT), SIGNAL(triggered()), SLOT(about()));
   connect(action(QUIT), SIGNAL(triggered()), &m_Application, SLOT(quit()));
}
