doProcess()
{
    mrpt::obs::CObservationCANBusJ1939Ptr	obs = mrpt::obs::CObservationCANBusJ1939::Create();
    bool thereIsObservation;
    bool hardwareError;

    doProcessSimple( thereIsObservation, *obs, hardwareError );
    if( thereIsObservation )
        appendObservation(obs);
    else
        cout << "No frame received" << endl;
}
