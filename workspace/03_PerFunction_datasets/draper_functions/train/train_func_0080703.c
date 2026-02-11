stick() {

    m_state.stuck = !m_state.stuck;

    if (m_initialized) {
        stateSig().emit(*this);

        m_workspacesig.emit(*this);
    }

    ClientList::iterator client_it = clientList().begin();
    ClientList::iterator client_it_end = clientList().end();
    for (; client_it != client_it_end; ++client_it) {

        WinClient::TransientList::const_iterator it = (*client_it)->transientList().begin();
        WinClient::TransientList::const_iterator it_end = (*client_it)->transientList().end();
        for (; it != it_end; ++it) {
            if ((*it)->fbwindow())
                (*it)->fbwindow()->setStuck(m_state.stuck);
        }

    }

}
