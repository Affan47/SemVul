orderFabHoverLeave() {
    m_fireQuoteTimer.stop();

    if (m_rolloverQuoteDialog) {
        m_rolloverQuoteDialog->hide();
    }
}
