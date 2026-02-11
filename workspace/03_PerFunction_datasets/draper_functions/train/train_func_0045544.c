buttonPressEvent(XButtonEvent &event) {
    setInputFocus();
    if (event.window == window()) {
        std::string::size_type i;
        std::string::size_type click_pos = m_end_pos;
        int delta = width();
        int tmp = 0;
        for(i = m_start_pos; i <= m_end_pos; i++) {
            tmp = abs(static_cast<int>
                      (event.x - font().textWidth(m_text.visual().c_str() + m_start_pos, i - m_start_pos)));

            if (tmp < delta) {
                delta = tmp;
                click_pos = i;
            }
        }
        m_cursor_pos = click_pos - m_start_pos;
        clear();
    }
}
