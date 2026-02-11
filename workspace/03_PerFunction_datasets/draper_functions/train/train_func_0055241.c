line(const Vertex &a, const Vertex &b)
{
    Vertex v[2] = { a, b };

    if (a.y() == b.y()) {
        std::sort(v, v+2, cmpX);
        return straightLineX(v[0].x(), v[1].x(), a.y());
    }

    if (a.x() == b.x()) {
        std::sort(v, v+2, cmpY);
        return straightLineY(v[0].y(), v[1].y(), a.x());
    }

    bool steep = fabs(v[1].y() - v[0].y()) > fabs(v[1].x() - v[0].x());
    if (steep) {
        std::swap(v[0][0], v[0][1]);
        std::swap(v[1][0], v[1][1]);
    }
    std::sort(v, v+2, cmpX);

    float dx = v[1].x()-v[0].x();
    float dy = (v[1].y()-v[0].y())/dx;
    float error = 0;
    int sign = dy > 0 ? 1 : -1;
    int y = v[0].y();


    for (int x = v[0].x(); x <= v[1].x(); x++) {
        if (steep)
            plot(y, x, 0, m_color);
        else
            plot(x, y, 0, m_color);
        error += dy;
        if (fabs(error) >= 0.5) {
            y += sign;
            error -= sign;
        }
    }
}
