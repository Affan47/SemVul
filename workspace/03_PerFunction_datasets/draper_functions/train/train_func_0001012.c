validatePage()
{
    if (name->text() != "") {

        DeviceConfigurations all;
        DeviceConfiguration add;


        add.type = wizard->type;
        add.name = name->text();
        add.portSpec = port->text();
        add.deviceProfile = profile->text();
        add.defaultString = QString(defWatts->isChecked() ? "P" : "") +
                                     QString(defBPM->isChecked() ? "H" : "") +
                                     QString(defRPM->isChecked() ? "C" : "") +
                                     QString(defKPH->isChecked() ? "S" : "");
        add.postProcess = virtualPower->currentIndex();

        switch (wheelSize->currentIndex()) {

            default:
            case 0: add.wheelSize = 2100 ; break;
            case 1: add.wheelSize = 1960 ; break;
            case 2: add.wheelSize = 1985 ; break;
            case 3: add.wheelSize = 1750 ; break;
        }

        QList<DeviceConfiguration> list = all.getList();
        list.insert(0, add);


        all.writeConfig(list);


        wizard->main->notifyConfigChanged();


        if (wizard->controller) {
            wizard->controller->stop();
#ifdef WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
            delete wizard->controller;
            wizard->controller = NULL;
        }
        return true;
    }
    return false;
}
