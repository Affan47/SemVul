initApm( struct SensorModul* sm )
{
  if ( updateApm() < 0 ) {
    ApmOK = -1;
    return;
  } else
    ApmOK = 1;

  registerMonitor( "apm/batterycharge", "integer", printApmBatFill, printApmBatFillInfo, sm );
  registerMonitor( "apm/remainingtime", "integer", printApmBatTime, printApmBatTimeInfo, sm );
}
