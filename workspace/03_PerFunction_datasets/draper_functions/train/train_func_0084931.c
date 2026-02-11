qcCheckDarkLevel(VimosImage *dark, VimosTable *ccdTable, double maxDev,
                 unsigned int warnOnly, unsigned int rCalc)
{

  const char fctid[] = "qcCheckDarkLevel";

  char      *keyname = pil_strdup(pilTrnGetKeyword("DarkLevel"));
  char       comment[COMMENT_LENGTH];

  double     median, nominal, offset, sigma;


  pilErrno = P_ENOERR;


  if (rCalc || readDoubleDescriptor(dark->descs, keyname, &median, comment)
      == VM_FALSE) {
    cpl_msg_info(fctid, "Calculating image median...");
    median = imageMedian(dark);
    writeFloatDescriptor(&(dark->descs), keyname, median,
                         "Median dark level");
  }
  else
    cpl_msg_info(fctid, "Retrieving image median from header (%s)...", keyname);

  cpl_msg_info(fctid, "Median dark level: %.4f", median);


  if (readDoubleDescriptor(ccdTable->descs, keyname, &nominal, comment)
      == VM_FALSE) {
    cpl_msg_error(fctid, "Invalid CCD table! Descriptor '%s' not found",
                keyname);

    pilErrno = P_EGENERIC;
    pil_free(keyname);

    return EXIT_FAILURE;
  }

  cpl_msg_info(fctid, "Nominal dark level: %.4f", nominal);


  offset = median - nominal;
  sigma = maxDev * imageAverageDeviation(dark, median);

  if (fabs(offset) > sigma) {
    if (!warnOnly) {
      cpl_msg_error(fctid, "Median dark level offset exceeds maximum "
                  "tolerance value of %.2f sigma (%.4f)!", maxDev, sigma);

      pilErrno = P_ENOERR;
      pil_free(keyname);

      return EXIT_FAILURE;
    }
    else
      cpl_msg_warning(fctid, "Median dark level offset exceeds maximum "
                    "tolerance value of %.2f sigma (%.4f)!", maxDev, sigma);
  }
  else
    cpl_msg_info(fctid, "Median dark level within tolerance interval "
               "%.4f +/- %.4f (%.2f sigma)", nominal, sigma, maxDev);


  writeFloatDescriptor(&(dark->descs), pilTrnGetKeyword("DarkOffset"),
                       offset, "Offset from nominal dark level");


  pil_free(keyname);

  return EXIT_SUCCESS;

}
