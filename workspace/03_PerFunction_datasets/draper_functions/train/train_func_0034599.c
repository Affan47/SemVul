setSmoothingFromSlider()
{


    if (active) return;
    else active = true;

    if (rtPlot->smooth != smoothSlider->value()) {
        setSmoothing(smoothSlider->value());
        smoothLineEdit->setText(QString("%1").arg(rtPlot->smooth));
    }
    active = false;
}
