configUpdate()
{

    setCanvasBackground(GColor(CPLOTBACKGROUND));
    grid->enableX(false);
    QPen gridPen(GColor(CPLOTGRID));
    gridPen.setStyle(Qt::DotLine);
    grid->setPen(gridPen);
}
