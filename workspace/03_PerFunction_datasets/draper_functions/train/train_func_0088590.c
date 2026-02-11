canChangeCoding(
    const E_TransferSyntax oldRepType,
    const E_TransferSyntax newRepType) const
{
  E_TransferSyntax myXfer = EXS_RLELossless;
  DcmXfer newRep(newRepType);
  DcmXfer oldRep(oldRepType);
  if (oldRep.isNotEncapsulated() && (newRepType == myXfer)) return OFTrue;


  return OFFalse;
}
