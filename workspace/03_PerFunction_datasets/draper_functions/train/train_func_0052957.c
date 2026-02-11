describe(OfxImageEffectHandle effect)
{

  OfxStatus stat;
  if((stat = ofxuFetchHostSuites()) != kOfxStatOK)
    return stat;


  OfxPropertySetHandle effectProps;
  gEffectHost->getPropertySet(effect, &effectProps);


  gPropHost->propSetInt(effectProps, kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0, 0);


  gPropHost->propSetInt(effectProps, kOfxImageEffectPropSupportsMultipleClipDepths, 0, 0);


  gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedPixelDepths, 0, kOfxBitDepthByte);
  gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedPixelDepths, 1, kOfxBitDepthShort);
  gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedPixelDepths, 2, kOfxBitDepthFloat);


  gPropHost->propSetString(effectProps, kOfxPropLabel, 0, "OFX Rectangle");
  gPropHost->propSetString(effectProps, kOfxImageEffectPluginPropGrouping, 0, "OFX Example");


  gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedContexts, 0, kOfxImageEffectContextGenerator);
  gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedContexts, 1, kOfxImageEffectContextFilter);
  gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedContexts, 2, kOfxImageEffectContextGeneral);

  return kOfxStatOK;
}
