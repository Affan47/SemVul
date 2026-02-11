setDelay(int delay)
{
    if (hrPwPlot->delay != delay) {
        delaySlider->setValue(delay);
        delayEdit->setText(QString("%1").arg(delay));
        rDelaySlider->setValue(delay);
        rDelayEdit->setText(QString("%1").arg(delay));
        hrPwPlot->delay = delay;
        hrPwPlot->recalc();
    }
}
