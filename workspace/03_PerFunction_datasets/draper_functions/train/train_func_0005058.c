arrangeCtct(bool set)
{
    outDebug(3, std::cout << "ctct " << (set ? "true" : "false") << std::endl);
    if (set)
    {
        arrangeCtc(!set);
        arrangeLcs(!set);
        arrangeQeth(!set);
        ui.hostIP->setInputMask("000.000.000.000;");
    }
    ui.hostIPLabel->setVisible(set);
    ui.hostIP->setVisible(set);
    ui.hostPortLabel->setVisible(set);
    ui.hostPortSpinbox->setVisible(set);
    ui.lportLabel->setVisible(set);
    ui.lportSpinbox->setVisible(set);
    ui.buffsizeLabel->setVisible(set);
    ui.buffsizeSpinBox->setVisible(set);

    ui.hostIPLabel->setGeometry(20,30,53,16);
    ui.hostIP->setGeometry(110,20,113,26);
    ui.hostPortLabel->setGeometry(240,30,61,16);
    ui.hostPortSpinbox->setGeometry(320,20,61,26);
    ui.lportLabel->setGeometry(20,70,61,16);
    ui.lportSpinbox->setGeometry(110,60,61,26);
    ui.buffsizeLabel->setGeometry(20,110,71,16);
    ui.buffsizeSpinBox->setGeometry(110,100,71,26);
}
