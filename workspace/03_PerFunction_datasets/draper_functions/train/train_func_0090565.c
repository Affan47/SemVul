GetSpacingTagFromMediaStorage(MediaStorage const &ms)
{
  Tag t;


  switch(ms)
    {


  case MediaStorage::CTImageStorage:
  case MediaStorage::MRImageStorage:
  case MediaStorage::RTDoseStorage:
  case MediaStorage::NuclearMedicineImageStorage:
  case MediaStorage::PETImageStorage:
  case MediaStorage::GeneralElectricMagneticResonanceImageStorage:
  case MediaStorage::PhilipsPrivateMRSyntheticImageStorage:

    t = Tag(0x0028,0x0030);
    break;
  case MediaStorage::ComputedRadiographyImageStorage:
  case MediaStorage::DigitalXRayImageStorageForPresentation:
  case MediaStorage::DigitalXRayImageStorageForProcessing:
  case MediaStorage::DigitalMammographyImageStorageForPresentation:
  case MediaStorage::DigitalMammographyImageStorageForProcessing:
  case MediaStorage::DigitalIntraoralXrayImageStorageForPresentation:
  case MediaStorage::DigitalIntraoralXRayImageStorageForProcessing:
  case MediaStorage::XRayAngiographicImageStorage:
  case MediaStorage::XRayRadiofluoroscopingImageStorage:
  case MediaStorage::XRayAngiographicBiPlaneImageStorageRetired:

    t = Tag(0x0018,0x1164);
    break;
  case MediaStorage::RTImageStorage:
    t = Tag(0x3002,0x0011);
    break;
  case MediaStorage::SecondaryCaptureImageStorage:
  case MediaStorage::MultiframeSingleBitSecondaryCaptureImageStorage:
  case MediaStorage::MultiframeGrayscaleByteSecondaryCaptureImageStorage:
  case MediaStorage::MultiframeGrayscaleWordSecondaryCaptureImageStorage:
  case MediaStorage::MultiframeTrueColorSecondaryCaptureImageStorage:


    t = Tag(0x0018,0x2010);
    break;
  case MediaStorage::HardcopyGrayscaleImageStorage:
    t = Tag(0xffff,0xffff);
    break;
  case MediaStorage::GEPrivate3DModelStorage:
  case MediaStorage::Philips3D:
  case MediaStorage::VideoEndoscopicImageStorage:
    gdcmWarningMacro( "FIXME" );
    t = Tag(0xffff,0xffff);
    break;
  case MediaStorage::UltrasoundMultiFrameImageStorage:


    gdcmWarningMacro( "FIXME" );
    t = Tag(0xffff,0xffff);
    break;
  case MediaStorage::UltrasoundImageStorage:
  case MediaStorage::UltrasoundImageStorageRetired:
  case MediaStorage::UltrasoundMultiFrameImageStorageRetired:

    t = Tag(0xffff,0xffff);
    t = Tag(0x0028,0x0034);
    break;
  default:
    gdcmDebugMacro( "Do not handle: " << ms );
    t = Tag(0xffff,0xffff);
    break;
    }


  if( ForcePixelSpacing && t == Tag(0xffff,0xffff) )
    {
    t = Tag(0x0028,0x0030);
    }

  return t;
}
