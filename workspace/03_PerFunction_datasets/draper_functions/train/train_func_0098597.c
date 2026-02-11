GetTransitivePropertyLinkLibraries(
                                      const char* config,
                                      cmTarget *headTarget,
                                      std::vector<std::string> &libs)
{
  cmTarget::LinkInterface const* iface = this->GetLinkInterface(config,
                                                                headTarget);
  if (!iface)
    {
    return;
    }
  if(this->GetType() != STATIC_LIBRARY
      || this->GetPolicyStatusCMP0022() == cmPolicies::WARN
      || this->GetPolicyStatusCMP0022() == cmPolicies::OLD)
    {
    libs = iface->Libraries;
    return;
    }

  const char* linkIfaceProp = "INTERFACE_LINK_LIBRARIES";
  const char* interfaceLibs = this->GetProperty(linkIfaceProp);

  if (!interfaceLibs)
    {
    return;
    }


  cmListFileBacktrace lfbt;
  cmGeneratorExpression ge(lfbt);
  cmGeneratorExpressionDAGChecker dagChecker(lfbt, this->GetName(),
                                              linkIfaceProp, 0, 0);
  dagChecker.SetTransitivePropertiesOnly();
  cmSystemTools::ExpandListArgument(ge.Parse(interfaceLibs)->Evaluate(
                                      this->Makefile,
                                      config,
                                      false,
                                      headTarget,
                                      this, &dagChecker), libs);
}
