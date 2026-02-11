setOrientation(FbTk::Orientation orient) {

    if (orient == m_orientation
        || !m_font->validOrientation(orient))
        return false;

    invalidateBackground();

    if (((m_orientation == FbTk::ROT0 || m_orientation == FbTk::ROT180) &&
         (orient == FbTk::ROT90 || orient == FbTk::ROT270)) ||
        ((m_orientation == FbTk::ROT90 || m_orientation == FbTk::ROT270) &&
         (orient == FbTk::ROT0 || orient == FbTk::ROT180))) {

        m_orientation = orient;
        resize(height(), width());
    } else {
        m_orientation = orient;
    }

    return true;
}
