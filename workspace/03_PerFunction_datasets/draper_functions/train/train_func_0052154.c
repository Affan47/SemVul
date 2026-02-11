transformItem(const QTransform & currTransf, bool includeRatsnest) {
    Q_UNUSED(currTransf);
    Q_UNUSED(includeRatsnest);

    if (m_textThings.count() == 0) {
        initTextThings();
    }

    double rotation;
    QTransform chiefTransform = layerKinChief()->transform();
    bool isFlipped = GraphicsUtils::isFlipped(chiefTransform.toAffine(), rotation);
    QString svg;
    if (isFlipped) {
        svg = makeFlipTextSvg();
    }

    if (svg.isEmpty()) {
        svg = this->property("textSvg").toByteArray();
    }

    if (rotation >= 135 && rotation <= 225) {
        svg = vflip(svg, isFlipped);
    }

    reloadRenderer(svg, true);

    QPointF p = layerKinChief()->sceneBoundingRect().topLeft();
    QTransform transform;
    QRectF bounds = boundingRect();
    transform.translate(bounds.width() / 2, bounds.height() / 2);
    transform.rotate(rotation);
    transform.translate(bounds.width() / -2, bounds.height() / -2);
    this->setTransform(transform);


}
