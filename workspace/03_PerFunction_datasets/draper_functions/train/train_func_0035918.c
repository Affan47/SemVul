getRealtimeData(RealtimeData &rtData)
{


    int Buttons, Status, Steering;
    double Power, HeartRate, Cadence, Speed, Distance;

    if(!myFortius->isRunning())
    {
        QMessageBox msgBox;
        msgBox.setText("Cannot Connect to Fortius");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        parent->Stop(1);
        return;
    }

    myFortius->getTelemetry(Power, HeartRate, Cadence, Speed, Distance, Buttons, Steering, Status);


    rtData.setWatts(Power);
    rtData.setHr(HeartRate);
    rtData.setCadence(Cadence);
    rtData.setSpeed(Speed);


    processRealtimeData(rtData);


    if (parent->calibrating) return;


    if ((Buttons&FT_PLUS)) parent->Higher();

    if ((Buttons&FT_MINUS)) parent->Lower();


    if (Buttons&FT_ENTER) parent->newLap();


    if (Buttons&FT_CANCEL) parent->Stop(0);


    rtData.setLoad(myFortius->getLoad());
    rtData.setSlope(myFortius->getGradient());
}
