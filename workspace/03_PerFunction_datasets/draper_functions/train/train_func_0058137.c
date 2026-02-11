loadPrintPreview(size_t idx, OFBool printLUT, OFBool changeStatus)
{
  OFCondition status = EC_IllegalCall;
  if ((pPrint != NULL) && (maximumPrintPreviewWidth > 0) && (maximumPrintPreviewHeight > 0))
  {
    const char *studyUID;
    const char *seriesUID;
    const char *instanceUID;
    if ((status = pPrint->getImageReference(idx, studyUID, seriesUID, instanceUID)) == EC_Normal)
    {
      status = EC_IllegalCall;
      const char *filename = getFilename(studyUID, seriesUID, instanceUID);
      if (filename)
      {
        DicomImage *image = new DicomImage(filename);
        if (image != NULL)
        {
          if (image->getStatus() == EIS_Normal)
          {
            unsigned long width = maximumPrintPreviewWidth;
            unsigned long height = maximumPrintPreviewHeight;

            double ratio = image->getWidthHeightRatio();
            const double mpWidth = getMonitorPixelWidth();
            const double mpHeight = getMonitorPixelHeight();
            if ((mpWidth > 0) && (mpHeight > 0))
              ratio *= (mpWidth / mpHeight);
            if (ratio == 0.0)
              ratio = 1.0;
            if (OFstatic_cast(double, image->getWidth()) / OFstatic_cast(double, width * ratio) <
                OFstatic_cast(double, image->getHeight()) / OFstatic_cast(double, height))
            {
              width = 0;
            } else
              height = 0;
            image->setWidthHeightRatio(ratio);
            pHardcopyImage = image->createScaledImage(width, height, 0 , 1 );
            if (pHardcopyImage != NULL)
            {
              if (pHardcopyImage->getStatus() == EIS_Normal)
              {

                if (displayFunction != NULL)
                  pHardcopyImage->setDisplayFunction(displayFunction[DVPSD_GSDF]);

                const char *polarity = pPrint->getImagePolarity(idx);
                if ((polarity != NULL) && (strcmp(polarity, "REVERSE") == 0))
                  pHardcopyImage->setPolarity(EPP_Reverse);

                DVPSPresentationLUT *plut = pPrint->getPresentationLUT();
                if (plut == NULL)
                  plut = pPrint->getImagePresentationLUT(idx);
                if (plut != NULL)
                {
                  pHardcopyImage->setHardcopyParameters(pPrint->getMinDensityValue(), pPrint->getMaxDensityValue(),
                      pPrint->getPrintReflectedAmbientLight(), pPrint->getPrintIllumination());
                  plut->activate(pHardcopyImage, printLUT);
                }
                status = EC_Normal;
                if (changeStatus)
                    instanceReviewed(studyUID, seriesUID, instanceUID);
              } else
                unloadPrintPreview();
            } else
              DCMPSTAT_LOGFILE("Load hardcopy grayscale image for print preview failed: memory exhausted");
          } else
            DCMPSTAT_LOGFILE("Load hardcopy grayscale image for print preview failed: could not read image");
          delete image;
        } else
          DCMPSTAT_LOGFILE("Load hardcopy grayscale image for print preview failed: memory exhausted");
      } else
        DCMPSTAT_LOGFILE("Load hardcopy grayscale image for print preview failed: UIDs not in index file");
    }
  }
  return status;
}
