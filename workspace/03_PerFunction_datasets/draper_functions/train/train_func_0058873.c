layoutCaret()
{
    if (isEmpty() || !caretPos().node()->renderer()) {
        m_caretX = m_caretY = m_caretSize = 0;
    }
    else {


        int w;
        int offset = RenderPosition::fromDOMPosition(caretPos()).renderedOffset();
#ifdef DEBUG_CARET
        kDebug(6200) << "[before caretPos()]" << m_caretX << endl;
#endif
        caretPos().node()->renderer()->caretPos(offset, true, m_caretX, m_caretY, w, m_caretSize);
#ifdef DEBUG_CARET
        kDebug(6200) << "[after caretPos()]" << m_caretX << endl;
#endif
    }

    m_needsCaretLayout = false;
}
