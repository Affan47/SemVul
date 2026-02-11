update_output_parameters(int selectedDevice, const PaDeviceInfo *deviceInfo)
{

  myOutputParameters.device = selectedDevice;

  myOutputParameters.channelCount = 1;
  myOutputParameters.sampleFormat = paInt16;


  if (deviceInfo)
    {
      double aLatency = deviceInfo->defaultLowOutputLatency;


      myOutputParameters.suggestedLatency =  aLatency;
      SHOW("Device=%d, myOutputParameters.suggestedLatency=%f, aCoeff=%f\n",
	   selectedDevice,
	   myOutputParameters.suggestedLatency,
	   aCoeff);
    }
  else
    {
      myOutputParameters.suggestedLatency = (double)0.1;
      SHOW("Device=%d, myOutputParameters.suggestedLatency=%f (default)\n",
	   selectedDevice,
	   myOutputParameters.suggestedLatency);
    }


  myOutputParameters.hostApiSpecificStreamInfo = NULL;
}
