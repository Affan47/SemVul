GatherSensorData()

{ char buffer[CF_BUFSIZE];

 Debug("GatherSensorData()\n");

 switch(VSYSTEMHARDCLASS)
    {
    case linuxx:


        if (ACPI && GetAcpi())
           {
           return;
           }

        if (LMSENSORS && GetLMSensors())
           {
           return;
           }

        break;

    case solaris:
        break;
    }
}
