peakPowerCustomClicked()
{
    intervalTypeWidget->show();
    if (typeDistance->isChecked())
        typeDistanceClicked();
    else
        typeTimeClicked();
    intervalCountWidget->show();
}
