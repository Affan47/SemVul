createRadialGradient(float x0, float y0, float r0,
                                                              float x1, float y1, float r1,
                                                              int& exceptionCode) const
{
    exceptionCode = 0;

    if (r0 < 0.0f || r1 < 0.0f) {
        exceptionCode = DOMException::INDEX_SIZE_ERR;
        return 0;
    }

    QPointF center, focalPoint;
    float radius, innerRadius;
    bool inverse;


    if (r1 > r0) {
        center      = QPointF(x1, y1);
        focalPoint  = QPointF(x0, y0);
        radius      = r1;
        innerRadius = (r1 > 0.0f ? r0 / r1 : 0.0f);
        inverse     = false;
    } else {
        center      = QPointF(x0, y0);
        focalPoint  = QPointF(x1, y1);
        radius      = r0;
        innerRadius = (r0 > 0.0f ? r1 / r0 : 0.0f);
        inverse     = true;
    }

    QGradient *gradient = new QRadialGradient(center, radius, focalPoint);
    return new CanvasGradientImpl(gradient, innerRadius, inverse);
}
