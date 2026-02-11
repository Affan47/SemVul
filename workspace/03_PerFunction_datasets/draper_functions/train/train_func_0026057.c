zonesChanged()
{
    pfPvPlot->refreshZoneItems();
    pfPvPlot->replot();
    qaCPValue->setText(QString("%1").arg(pfPvPlot->getCP()));
}
