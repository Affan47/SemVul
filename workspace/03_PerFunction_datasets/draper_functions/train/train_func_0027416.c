intersect(const IntRect& other)
{
    int l = max(x(), other.x());
    int t = max(y(), other.y());
    int r = min(right(), other.right());
    int b = min(bottom(), other.bottom());


    if (l >= r || t >= b) {
        l = 0;
        t = 0;
        r = 0;
        b = 0;
    }

    m_location.setX(l);
    m_location.setY(t);
    m_size.setWidth(r - l);
    m_size.setHeight(b - t);
}
