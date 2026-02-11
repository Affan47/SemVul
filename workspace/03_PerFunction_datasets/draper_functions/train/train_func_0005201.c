nodeAtPoint(RenderObject::NodeInfo& info, int _x, int _y, int _tx, int _ty)
{

    if (m_markupBox) {
        _tx += m_x + m_width - m_markupBox->xPos();
        _ty += m_y + m_baseline - (m_markupBox->yPos() + m_markupBox->baseline());
        if (m_markupBox->nodeAtPoint(info, _x, _y, _tx, _ty)) {
            object()->setInnerNode(info);
            return true;
        }
    }

    QRect rect(_tx + m_x, _ty + m_y, m_width, m_height);
    if (object()->style()->visibility() == VISIBLE && rect.contains(_x, _y)) {
        object()->setInnerNode(info);
        return true;
    }
    return false;
}
