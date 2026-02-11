point(void) const
{
    if (_shapeRef)
    {
        const Polygon& poly = _shapeRef->polygon();

        double x_min = DBL_MAX;
        double x_max = -DBL_MAX;
        double y_min = DBL_MAX;
        double y_max = -DBL_MAX;
        for (size_t i = 0; i < poly.size(); ++i)
        {
            x_min = std::min(x_min, poly.ps[i].x);
            x_max = std::max(x_max, poly.ps[i].x);
            y_min = std::min(y_min, poly.ps[i].y);
            y_max = std::max(y_max, poly.ps[i].y);
        }

        Point point;


        point.vn = kUnassignedVertexNumber;
        if (_xPosition == ATTACH_POS_LEFT)
        {
            point.x = x_min + _insideOffset;
            point.vn = 6;
        }
        else if (_xPosition == ATTACH_POS_RIGHT)
        {
            point.x = x_max - _insideOffset;
            point.vn = 4;
        }
        else
        {
            point.x = x_min + (_xPosition * (x_max - x_min));
        }

        if (_yPosition == ATTACH_POS_TOP)
        {
            point.y = y_max - _insideOffset;
            point.vn = 5;
        }
        else if (_yPosition == ATTACH_POS_BOTTOM)
        {
            point.y = y_min + _insideOffset;
            point.vn = 7;
        }
        else
        {
            point.y = y_min + (_yPosition * (y_max - y_min));
            point.vn = kUnassignedVertexNumber;
        }

        return point;
    }
    else
    {
        return _point;
    }
}
