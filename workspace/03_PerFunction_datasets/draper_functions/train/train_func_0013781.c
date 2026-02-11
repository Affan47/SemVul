DefaultSensorConstants(UInt8 id)
  {
    switch((int)id)
    {
    case type_Kistler_9821B:

			SensorSeparation.X = 120.0;
			SensorSeparation.Y = 200.0;
			SensorSeparation.Z = 54.0;
      break;

    case type_Kistler_9826:

			SensorSeparation.X = 120.0;
			SensorSeparation.Y = 200.0;
			SensorSeparation.Z = 49.0;
      break;

    case type_Kistler_9821C_1:

			SensorSeparation.X = 120.0;
			SensorSeparation.Y = 200.0;
			SensorSeparation.Z = 49.0;
      break;

    case type_Kistler_9821C_2:

			SensorSeparation.X = 175.0;
			SensorSeparation.Y = 275.0;
			SensorSeparation.Z = 22.0;
      break;

    case type_Kistler_9827:

			SensorSeparation.X = 210.0;
			SensorSeparation.Y = 350.0;
			SensorSeparation.Z = 52.0;
      break;

    case type_Kistler_9261:

			SensorSeparation.X = 132.0;
			SensorSeparation.Y = 220.0;
			SensorSeparation.Z = 37.0;
      break;

    case type_AMTI_BP2416:
    case type_AMTI_LG6:
		case type_AMTI_OR6_7:
    case type_AMTI_AccuSway:

			CentreOffset.X = 0.0;
			CentreOffset.Y = 0.0;
			CentreOffset.Z = 61.0;
      break;

		case type_AMTI_AccuGait:

			CentreOffset.X = 0.0;
			CentreOffset.Y = 0.0;
			CentreOffset.Z = 61.0;
      break;
    }
  }
