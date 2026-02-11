pointHover(QwtPlotCurve *curve, int index)
{
    if (index >= 0) {

        double yvalue = curve->sample(index).y();
        double xvalue = curve->sample(index).x();


        QString text = QString("%1 %2\n%3 %4")
                        .arg(yvalue, 0, 'f', 0)
                        .arg(this->axisTitle(curve->yAxis()).text())
                        .arg(xvalue, 0, 'f', 2)
                        .arg(this->axisTitle(curve->xAxis()).text());


        tooltip->setText(text);
    } else {
        tooltip->setText("");
    }
}
