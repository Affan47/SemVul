getString() const {
    switch (m_value) {
    case Slit::TOPLEFT:
        return string("TopLeft");
        break;
    case Slit::LEFTCENTER:
        return string("LeftCenter");
        break;
    case Slit::BOTTOMLEFT:
        return string("BottomLeft");
        break;
    case Slit::TOPCENTER:
        return string("TopCenter");
        break;
    case Slit::BOTTOMCENTER:
        return string("BottomCenter");
        break;
    case Slit::TOPRIGHT:
        return string("TopRight");
        break;
    case Slit::RIGHTCENTER:
        return string("RightCenter");
        break;
    case Slit::BOTTOMRIGHT:
        return string("BottomRight");
        break;
    case Slit::LEFTTOP:
        return string("LeftTop");
        break;
    case Slit::RIGHTTOP:
        return string("RightTop");
        break;
    case Slit::LEFTBOTTOM:
        return string("LeftBottom");
        break;
    case Slit::RIGHTBOTTOM:
        return string("RightBottom");
        break;
    }

    return string("RightBottom");
}
