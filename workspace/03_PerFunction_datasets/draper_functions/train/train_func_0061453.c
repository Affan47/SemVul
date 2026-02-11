createDummyValues(OFBool replaceSOPInstanceUID)
{
  OFCondition result = EC_Normal;
  char uid[100];
  OFString aString;

  DVPSHelper::setDefault(result, patientName, DEFAULT_patientName);
  SET_UID(studyInstanceUID)
  SET_UID(seriesInstanceUID)

  DVPSHelper::setDefault(result, imageNumber, DEFAULT_imageNumber);
  DVPSHelper::setDefault(result, presentationLabel, DEFAULT_presentationLabel);
  DVPSHelper::currentDate(aString);
  DVPSHelper::setDefault(result, presentationCreationDate, aString.c_str() );
  DVPSHelper::currentTime(aString);
  DVPSHelper::setDefault(result, presentationCreationTime, aString.c_str() );

  if ((result==EC_Normal)&&(replaceSOPInstanceUID ||(sOPInstanceUID.getLength()==0)))
  {
    sOPInstanceUID.putString(dcmGenerateUniqueIdentifier(uid));
    DVPSHelper::currentDate(aString);
    DVPSHelper::setDefault(result, instanceCreationDate, aString.c_str() );
    DVPSHelper::currentTime(aString);
    DVPSHelper::setDefault(result, instanceCreationTime, aString.c_str() );
  }


  if (shutterPresentationValue.getVM() != 1) shutterPresentationValue.putUint16(0);
  DVPSHelper::setDefault(result, shutterLeftVerticalEdge, "1");
  DVPSHelper::setDefault(result, shutterRightVerticalEdge, "1024");
  DVPSHelper::setDefault(result, shutterUpperHorizontalEdge, "1");
  DVPSHelper::setDefault(result, shutterLowerHorizontalEdge, "1024");
  DVPSHelper::setDefault(result, centerOfCircularShutter, "512\\512");
  DVPSHelper::setDefault(result, radiusOfCircularShutter, "512");
  DVPSHelper::setDefault(result, verticesOfThePolygonalShutter, "1\\1\\1\\1024\\1024\\1024\\1024\\1\\1\\1");
  if (shutterOverlayGroup.getVM() != 1) shutterOverlayGroup.putUint16(0x6000);


  if (result==EC_Normal)
  {
    if (imageRotation.getVM() != 1) result = imageRotation.putUint16(0);
  }
  DVPSHelper::setDefault(result, imageHorizontalFlip, "N");


  DVPSHelper::setDefault(result, rescaleIntercept, "0");
  DVPSHelper::setDefault(result, rescaleSlope, "1");
  DVPSHelper::setDefault(result, rescaleType, "UNSPECIFIED");

  return result;
}
