getString() const {

    size_t i = (m_value == FbTk::Util::clamp(m_value, FbWinFrame::TOPLEFT, FbWinFrame::RIGHTTOP)
                ? m_value
                : FbWinFrame::DEFAULT) - 1;
    return placement_strings[i].str;
}
