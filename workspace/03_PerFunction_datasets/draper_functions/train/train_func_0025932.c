setPerComponentScaleEnabledness( OfxImageEffectHandle effect)
{

  MyInstanceData *myData = getMyInstanceData(effect);


  int perComponentScale;
  gParamHost->paramGetValue(myData->perComponentScaleParam, &perComponentScale);

  if(ofxuIsClipConnected(effect, kOfxImageEffectSimpleSourceClipName)) {
    OfxPropertySetHandle props; gEffectHost->clipGetPropertySet(myData->sourceClip, &props);


    char *pixelType;
    gPropHost->propGetString(props, kOfxImageEffectPropComponents, 0, &pixelType);


    perComponentScale = perComponentScale && !(strcmp(pixelType, kOfxImageComponentAlpha) == 0);
  }


  setParamEnabledness(effect, "scaleR", perComponentScale);
  setParamEnabledness(effect, "scaleG", perComponentScale);
  setParamEnabledness(effect, "scaleB", perComponentScale);
  setParamEnabledness(effect, "scaleA", perComponentScale);
}
