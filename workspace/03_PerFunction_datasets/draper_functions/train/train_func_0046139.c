createConnection(Server &server,
                                                           const DBusConnectionPtr &conn,
                                                           const std::string &sessionID,
                                                           const StringMap &peer,
                                                           bool must_authenticate)
{
    boost::shared_ptr<Connection> c(new Connection(server, conn, sessionID, peer, must_authenticate));
    c->m_me = c;
    return c;
}
