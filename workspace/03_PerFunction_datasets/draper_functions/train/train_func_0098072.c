setShapeGesture(const KShapeGesture &gst)
{
    if (!m_oldShapeGesture) {
        m_oldShapeGesture = new KShapeGesture(gst);
    }
    m_action->setShapeGesture(gst);
    updateModified();
}
