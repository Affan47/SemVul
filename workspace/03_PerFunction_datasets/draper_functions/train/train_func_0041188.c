Calibrate()
{
    static QProgressDialog *bar=NULL;


    if (calibrating) {
        bar->reset();


        session_time.start();
        lap_time.start();
        load_period.restart();
        if (status & RT_WORKOUT) load_timer->start(LOADRATE);
        if (status & RT_RECORDING) disk_timer->start(SAMPLERATE);
        main->notifyUnPause();


        if (status&RT_MODE_ERGO) {

            foreach(int dev, devices()) {
                Devices[dev].controller->setMode(RT_MODE_ERGO);
                Devices[dev].controller->setLoad(load);
            }
        } else {

            foreach(int dev, devices()) {
                Devices[dev].controller->setMode(RT_MODE_SPIN);
                Devices[dev].controller->setGradient(slope);
            }
        }

    } else {

        if (bar == NULL) {
            QString title = tr("Calibrating...\nPress F3 on Controller when done.");
            bar = new QProgressDialog(title, tr("Done"), 0, 0, this);
            bar->setWindowModality(Qt::WindowModal);
            bar->setMinimumDuration(0);
            bar->setAutoClose(true);
            connect(bar, SIGNAL(canceled()), this, SLOT(Calibrate()));
        }
        bar->show();


        session_elapsed_msec += session_time.elapsed();
        lap_elapsed_msec += lap_time.elapsed();

        if (status & RT_RECORDING) disk_timer->stop();
        if (status & RT_WORKOUT) load_timer->stop();
        load_msecs += load_period.restart();

        main->notifyPause();


        foreach(int dev, devices())
            if (Devices[dev].type == DEV_CT)
                Devices[dev].controller->setMode(RT_MODE_CALIBRATE);
    }
    calibrating = !calibrating;
}
