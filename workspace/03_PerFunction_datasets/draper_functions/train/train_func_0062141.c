describeInContext( OfxImageEffectHandle  ,  OfxPropertySetHandle )
{
  if (!OFX::logOpenFile()) {
    std::cout << "Error: OFX Test Properties plugin cannot open log file " << OFX::logGetFileName() << std::endl;
  }
  return kOfxStatOK;
}
