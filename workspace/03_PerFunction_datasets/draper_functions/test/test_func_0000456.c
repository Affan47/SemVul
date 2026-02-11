configChanged()
{
    setCanvasBackground(GColor(CPLOTBACKGROUND));


    QwtSymbol sym;
    sym.setStyle(QwtSymbol::Ellipse);
    sym.setSize(6);
    sym.setPen(QPen(GColor(CPLOTSYMBOL)));
    sym.setBrush(QBrush(Qt::NoBrush));
    curve->setSymbol(new QwtSymbol(sym));
    curve->setStyle(QwtPlotCurve::Dots);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);


    QPen marker = GColor(CPLOTMARKER);
    QPen cp = GColor(CCP);
    mX->setLinePen(marker);
    mY->setLinePen(marker);
    cpCurve->setPen(cp);

    setCL(appsettings->value(this, GC_CRANKLENGTH).toDouble() / 1000.0);
}
