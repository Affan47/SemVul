svgMoveTo(double x1, double y1, bool closed, bool abs = true)
    {
        current.setX(narrowPrecisionToFloat(abs ? x1 : current.x() + x1));
        current.setY(narrowPrecisionToFloat(abs ? y1 : current.y() + y1));
        if (closed)
            m_path->closeSubpath();
        m_path->moveTo(current);
    }
