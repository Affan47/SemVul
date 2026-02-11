instanceChanged( OfxImageEffectHandle  effect,
		 OfxPropertySetHandle inArgs,
		 OfxPropertySetHandle )
{

  char *changeReason;
  gPropHost->propGetString(inArgs, kOfxPropChangeReason, 0, &changeReason);


  if(strcmp(changeReason, kOfxChangeUserEdited) != 0) return kOfxStatReplyDefault;


  char *typeChanged;
  gPropHost->propGetString(inArgs, kOfxPropType, 0, &typeChanged);


  bool isClip = strcmp(typeChanged, kOfxTypeClip) == 0;
  bool isParam = strcmp(typeChanged, kOfxTypeParameter) == 0;


  char *objChanged;
  gPropHost->propGetString(inArgs, kOfxPropName, 0, &objChanged);


  if((isClip && strcmp(objChanged, kOfxImageEffectSimpleSourceClipName)  == 0) ||
     (isParam && strcmp(objChanged, "scaleComponents")  == 0)) {
    setPerComponentScaleEnabledness(effect);
    return kOfxStatOK;
  }


  return kOfxStatReplyDefault;
}
