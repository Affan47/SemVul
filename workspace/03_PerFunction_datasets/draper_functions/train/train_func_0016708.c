ComputeTargetMediaStorage()
{
  MediaStorage ms;
  if( !ms.SetFromFile( GetFile() ) )
  {

    ms = ImageHelper::ComputeMediaStorageFromModality( ms.GetModality(),
        PixelData->GetNumberOfDimensions(),
        PixelData->GetPixelFormat(),
        PixelData->GetPhotometricInterpretation(),
        GetImage().GetIntercept(), GetImage().GetSlope() );
  }

  if( ms == MediaStorage::MRImageStorage &&
    ( GetImage().GetIntercept() != 0.0 || GetImage().GetSlope() != 1.0 ) )
  {
    ms = ImageHelper::ComputeMediaStorageFromModality( ms.GetModality(),
        PixelData->GetNumberOfDimensions(),
        PixelData->GetPixelFormat(),
        PixelData->GetPhotometricInterpretation(),
        GetImage().GetIntercept(), GetImage().GetSlope() );
  }

  if( ms == MediaStorage::MultiframeGrayscaleByteSecondaryCaptureImageStorage
   || ms == MediaStorage::MultiframeGrayscaleWordSecondaryCaptureImageStorage )
  {
    ms = ImageHelper::ComputeMediaStorageFromModality( ms.GetModality(),
        PixelData->GetNumberOfDimensions(),
        PixelData->GetPixelFormat(),
        PixelData->GetPhotometricInterpretation(),
        GetImage().GetIntercept(), GetImage().GetSlope() );
  }
  return ms;
}
