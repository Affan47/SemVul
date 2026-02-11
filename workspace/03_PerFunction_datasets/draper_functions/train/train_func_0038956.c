isConstantBitrateMode(
        const QCDATA_BR_MODE bitrateMode
        )
{
  return ( ((bitrateMode==QCDATA_BR_MODE_CBR) || (bitrateMode==QCDATA_BR_MODE_SFR) || (bitrateMode==QCDATA_BR_MODE_FF)) ? 1 : 0 );
}
