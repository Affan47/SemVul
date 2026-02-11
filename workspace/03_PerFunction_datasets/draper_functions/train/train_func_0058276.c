terminalPointChanged(const QString & coord, double value)
{
    PEGraphicsItem * pegi = findConnectorItem();
    if (pegi == NULL) return;

    QPointF p = pegi->terminalPoint();
    if (coord == "x") {
      p.setX(qMax(qreal(0.0), qMin(qreal(value), pegi->rect().width())));
    }
    else {
      p.setY(qMax(qreal(0.0), qMin(qreal(value), pegi->rect().height())));
    }

    terminalPointChangedAux(pegi, pegi->terminalPoint(), p);
}
