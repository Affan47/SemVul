setDefaultPresentationLUTShape()
{
  OFCondition result = EC_Normal;
  if (currentImageMonochrome1) result=presentationLUT.setType(DVPSP_inverse); else result=presentationLUT.setType(DVPSP_identity);
  currentImagePLUTValid = OFFalse;
  imageInverse = presentationLUT.isInverse();
  return result;
}
