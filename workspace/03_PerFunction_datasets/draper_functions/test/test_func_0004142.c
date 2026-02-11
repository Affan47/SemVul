sizeClicked()
{
    if (ui.sizeCheckBox->isChecked())
    {
        ui.sizeSpinBox->setEnabled(true);
        setSizeValue();
    }
    else
    {
        ui.sizeSpinBox->setEnabled(false);
        setSizeValue();
    }
}
