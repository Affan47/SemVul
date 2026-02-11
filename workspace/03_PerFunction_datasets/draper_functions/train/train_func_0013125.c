check(GSource *source)
        {
            FDSource *fdsource = (FDSource *)source;
            if (fdsource->m_select->m_pollfd.revents) {
                fdsource->m_select->m_result = GLIB_SELECT_READY;
                return TRUE;
            } else {
                return FALSE;
            }
        }
