getBeamTemperature(VimosDescriptor *desc, double *temperature,
                   double tolerance, int quadrant)
{

  const char id[] = "getBeamTemperature";

  double ta;
  double tb;
  double tm;
  int    count;
  int    i;


  if (readDoubleDescriptor(desc, pilTrnGetKeyword("AmbientTemperature"),
                           &ta, NULL) == VM_FALSE) {
    cpl_msg_warning(id, "Cannot find descriptor %s",
                  pilTrnGetKeyword("AmbientTemperature"));
    return 1;
  }

  if (readDoubleDescriptor(desc, pilTrnGetKeyword("BeamTemperature", quadrant),
                           temperature, NULL) == VM_FALSE) {
    cpl_msg_warning(id, "Cannot find descriptor %s",
                  pilTrnGetKeyword("BeamTemperature", quadrant));
    return 1;
  }

  if (fabs(*temperature - ta) < tolerance)
    return 0;


  tm = 0.0;
  count = 0;
  for (i = 1; i <= 4; i++) {

    if (i == quadrant)
      continue;

    if (readDoubleDescriptor(desc, pilTrnGetKeyword("BeamTemperature", i),
                             &tb, NULL) == VM_FALSE) {


      cpl_msg_warning(id, "Beam temperature (%f) out of range! "
                    "Using ambient temperature (%f) instead!",
                    *temperature, ta);
      *temperature = ta;

      return 0;

    }
    else {
      if (fabs(tb - ta) < tolerance) {
        tm += tb;
        count++;
      }
    }

  }

  if (count) {
    cpl_msg_warning(id, "Beam temperature (%f) out of range! "
                  "Using estimate from other beam temperatures (%f) instead!",
                  *temperature, tm / count);
    *temperature = tm / count;
  }
  else {


    cpl_msg_warning(id, "Beam temperature (%f) out of range! "
                  "Using ambient temperature (%f) instead!",
                  *temperature, ta);
    *temperature = ta;
  }

  return 0;

}
