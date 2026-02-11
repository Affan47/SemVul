mode() const
{
    if(ui.modeCombo->currentIndex() == -1)
    {
        return 0;
    }
    return ui.modeCombo->itemData(ui.modeCombo->currentIndex()).toInt();
}
