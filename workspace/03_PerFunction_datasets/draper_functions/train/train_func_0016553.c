AddNewSockets()
        {
            ACE_GUARD (ACE_Thread_Mutex, Guard, m_NewSockets_Lock);

            if (m_NewSockets.empty())
                return;

            for (SocketSet::const_iterator i = m_NewSockets.begin(); i != m_NewSockets.end(); ++i)
            {
                WorldSocket* sock = (*i);

                if (sock->IsClosed())
                {
                    sock->RemoveReference();
                    --m_Connections;
                }
                else
                    m_Sockets.insert(sock);
            }

            m_NewSockets.clear();
        }
