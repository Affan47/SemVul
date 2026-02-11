done() {
        if (!m_terminationRequested)
            qApp->postEvent(m_receiver->q, new CompletionMatchEvent(this));
        else
            deleteLater();
    }
