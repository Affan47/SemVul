setFlip(OFBool isFlipped)
{

  DVPSRotationType rotation = getRotation();
  OFBool oldFlip = getFlip();
  displayedAreaSelectionList.rotateAndFlip(rotation, oldFlip, rotation, isFlipped);

  if (isFlipped) return imageHorizontalFlip.putString("Y");
  else return imageHorizontalFlip.putString("N");
}
