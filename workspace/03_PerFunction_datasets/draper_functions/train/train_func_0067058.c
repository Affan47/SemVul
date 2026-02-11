load(FbTk::Parser &p, FbTk::StringConvertor &m_labelconvertor) {
        p>>m_key>>m_label>>m_cmd>>m_icon;
        m_label.second = m_labelconvertor.recode(m_label.second);
    }
