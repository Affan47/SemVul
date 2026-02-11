mousePressEvent(QMouseEvent *ev)
    {
        if (ev->modifiers() & Qt::ShiftModifier) {
            QColor color = QColorDialog::getColor(Utils::StyleHelper::requestedBaseColor(), m_parent);
            if (color.isValid())
                Utils::StyleHelper::setBaseColor(color);
        }
    }
