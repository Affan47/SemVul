svgLineTo(double x1, double y1, bool abs = true)
    {
        current.setX(narrowPrecisionToFloat(abs ? x1 : current.x() + x1));
        current.setY(narrowPrecisionToFloat(abs ? y1 : current.y() + y1));
        m_path->addLineTo(current);
    }
