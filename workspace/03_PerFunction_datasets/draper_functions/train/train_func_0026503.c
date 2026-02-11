setFrameIntervalsPfPvFromCheckBox()
{
    if (pfPvPlot->frameIntervals() != frameIntervalPfPvCheckBox->isChecked()) {
        pfPvPlot->setFrameIntervals(frameIntervalPfPvCheckBox->isChecked());
        rFrameInterval->setChecked(frameIntervalPfPvCheckBox->isChecked());
    }
}
