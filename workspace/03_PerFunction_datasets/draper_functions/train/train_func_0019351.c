clear() {
    FbWindow::clear();

    int center_pos = (height() + font().ascent())/2;
    if (gc() == 0)
        setGC(DefaultGC(FbTk::App::instance()->display(), screenNumber()));

    font().drawText(*this, screenNumber(),
                    gc(),
                    m_text.visual().c_str() + m_start_pos,
                    m_end_pos - m_start_pos,
                    0, center_pos);


    int cursor_pos = font().textWidth(m_text.visual().c_str() + m_start_pos, m_cursor_pos) + 1;
    drawLine(gc(), cursor_pos, center_pos, cursor_pos, center_pos - font().height());
}
