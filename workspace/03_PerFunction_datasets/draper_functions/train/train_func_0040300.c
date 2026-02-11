linePoints() const
{
    Q_D( const LineAnnotation );

    if (!d->pdfAnnot)
        return d->linePoints;

    double MTX[6];
    d->fillTransformationMTX(MTX);

    QLinkedList<QPointF> res;
    if (d->pdfAnnot->getType() == Annot::typeLine)
    {
        const AnnotLine * lineann = static_cast<const AnnotLine*>(d->pdfAnnot);
        QPointF p;
        XPDFReader::transform(MTX, lineann->getX1(), lineann->getY1(), p);
        res.append(p);
        XPDFReader::transform(MTX, lineann->getX2(), lineann->getY2(), p);
        res.append(p);
    }
    else
    {
        const AnnotPolygon * polyann = static_cast<const AnnotPolygon*>(d->pdfAnnot);
        const AnnotPath * vertices = polyann->getVertices();

        for (int i = 0; i < vertices->getCoordsLength(); ++i)
        {
            QPointF p;
            XPDFReader::transform(MTX, vertices->getX(i), vertices->getY(i), p);
            res.append(p);
        }
    }

    return res;
}
