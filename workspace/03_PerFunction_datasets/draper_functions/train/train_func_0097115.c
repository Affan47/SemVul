slotSelectEngine(QListWidgetItem* currentItem, QListWidgetItem* previousItem)
{
    int previous = ui.engineList->row(previousItem);
    int current = ui.engineList->row(currentItem);

    if(previous != -1)
    {
        updateEngineData(previous);
    }

    if(current != -1)
    {
        ui.engineEditWidget->setEnabled(true);

        ui.engineName->setText(engineList[current].name);
        ui.engineCommand->setText(engineList[current].command);
        ui.engineOptions->setText(engineList[current].options);
        ui.engineDirectory->setText(engineList[current].directory);
        ui.engineOptionMore->setEnabled(true);
        if(engineList[current].protocol == EngineData::WinBoard)
        {
            ui.engineProtocolWinBoard->setChecked(true);
        }
        else
        {
            ui.engineProtocolUCI->setChecked(true);
        }
    }
    else
    {
        ui.engineName->clear();
        ui.engineCommand->clear();
        ui.engineOptions->clear();
        ui.engineDirectory->clear();
        ui.engineProtocolUCI->setChecked(true);
        ui.engineEditWidget->setEnabled(false);
        ui.engineOptionMore->setEnabled(false);
    }
}
