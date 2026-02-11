writeCurvatureModelString(VimosDescriptor **desc,
                                    VimosDistModelFull *crvMod)
{
  const char modName[] = "writeCurvatureModel";
  char      *descName;
  int        i, j, k;
  char       string[80];
  VimosBool  wrOK;

  descName = (char *) pilKeyTranslate("CurvatureOrd");
  if ((wrOK = writeIntDescriptor(desc, descName, crvMod->orderPol, ""))
                                                               == VM_TRUE) {
    descName = (char *) pilKeyTranslate("CurvatureOrdX");
    if ((wrOK = writeIntDescriptor(desc, descName, crvMod->orderX, ""))
                                                               == VM_TRUE) {
      descName = (char *) pilKeyTranslate("CurvatureOrdY");
      if ((wrOK = writeIntDescriptor(desc, descName,  crvMod->orderY, ""))
                                                               == VM_TRUE) {
        for (i = 0; i <= crvMod->orderPol; i++) {
          for (j = 0; j <= crvMod->orderX; j++) {
            for (k = 0; k <= crvMod->orderY; k++) {
              sprintf(string, "%#.14E", crvMod->coefs[i]->coefs[j][k]);
              descName = (char *) pilKeyTranslate("Curvature", i, j, k);
              if ((wrOK = writeStringDescriptor(desc, descName, string, ""))
                                                                == VM_FALSE) {
                cpl_msg_error(modName, "Cannot write descriptor %s", descName);
                return VM_FALSE;
              }
            }
          }
        }
      }
    }
  }

  if (wrOK == VM_FALSE)
    cpl_msg_error(modName, "Cannot write descriptor %s", descName);

  return wrOK;
}
