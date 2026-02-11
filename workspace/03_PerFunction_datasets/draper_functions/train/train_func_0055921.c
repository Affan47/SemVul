amdmsDetectParticleEvents(amdmsPARTICLE_EVENT_SETUP *setup,
				   amdmsDATA_FILTER_SETUP *filter,
				   amdmsCALIBRATION_SETUP *calib,
				   amdmsFITS *file,
				   amdmsDATA *meanPixels,
				   amdmsDATA *varPixels)
{
  int          iImage;
  int          iPE;
  amdmsDATA     rawData;
  amdmsDATA     calData;

  if (!setup->peFlag) {
    return amdmsSUCCESS;
  }

  if (amdmsFindPEs(setup, varPixels, filter->ioiTo - filter->ioiFrom + 1) != amdmsSUCCESS) {
    return amdmsFAILURE;
  }

  amdmsInitData(&rawData);
  amdmsInitData(&calData);
  for (iImage = filter->ioiFrom; iImage <= filter->ioiTo; iImage++) {
    if (amdmsReadData(file, &rawData, iImage, 0) != amdmsSUCCESS) {
      return amdmsFAILURE;
    }
    if (amdmsCalibrateData(calib, &rawData, &calData) != amdmsSUCCESS) {
      return amdmsFAILURE;
    }
    for (iPE = 0; iPE < setup->nPE; iPE++) {
      setup->pes[iPE].values[iImage - filter->ioiFrom] = calData.data[setup->pes[iPE].idx];
    }
  }
  amdmsFreeData(&rawData);
  amdmsFreeData(&calData);
  for (iPE = 0; iPE < setup->nPE; iPE++) {
    amdmsAnalyzePE(setup, iPE, varPixels->data[setup->pes[iPE].idx]);
    if (!setup->pes[iPE].isBad) {
      amdmsFindPEInterval(setup, iPE);
    }
  }
  for (iPE = 0; iPE < setup->nPE; iPE++) {
    if (setup->pes[iPE].isBad) continue;
    if (setup->pes[iPE].isPE) continue;
    amdmsVerifyPE(setup, iPE);
  }
  for (iPE = 0; iPE < setup->nPE; iPE++) {
    if (setup->pes[iPE].isBad) continue;
    if (!setup->pes[iPE].isPE) continue;
    if (setup->pes[iPE].isUpToDate) continue;
    amdmsRecalculateMeanVar(setup, filter, iPE, meanPixels, varPixels);
  }
  return 1;
}
