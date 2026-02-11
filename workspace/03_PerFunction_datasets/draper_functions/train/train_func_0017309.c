process(GErrorCXX &gerror) {

            m_view.connectSignal<void (EBookClientView *ebookview,
                                       const GSList *contacts)>("objects-added",
                                                                boost::bind(m_process, _2));
            m_view.connectSignal<void (EBookClientView *ebookview,
                                       const GError *error)>("complete",
                                                             boost::bind(&EBookClientViewSyncHandler::completed, this, _2));


            e_book_client_view_start (m_view, m_error);
            if (m_error) {
                std::swap(gerror, m_error);
                return false;
            }


            m_loop.run();
            e_book_client_view_stop (m_view, NULL);

            if (m_error) {
                std::swap(gerror, m_error);
                return false;
            } else {
                return true;
            }
        }
