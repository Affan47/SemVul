endExtension(const CompoundExtensionFlowObj &flowObj)
{
  Vector<StringC> portNames;
  flowObj.portNames(portNames);
  for (size_t i = 0; i < portNames.size(); i++) {
    Owner<SaveFOTBuilder> stream(save_.get());
    startExtensionStream(portNames[i]);
    stream->emit(*this);
    endExtensionStream(portNames[i]);
  }
  endExtensionSerial(flowObj);
}
