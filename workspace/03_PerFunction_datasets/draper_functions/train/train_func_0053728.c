to_vpi_tchktyp(word32 tctyp)
{
 switch ((byte) tctyp) {
  case TCHK_SETUP: return(vpiSetup);
  case TCHK_HOLD: return(vpiHold);
  case TCHK_WIDTH: return(vpiWidth);
  case TCHK_PERIOD: return(vpiPeriod);
  case TCHK_SKEW: return(vpiSkew);
  case TCHK_RECOVERY: return(vpiRecovery);
  case TCHK_NOCHANGE: return(vpiNoChange);
  case TCHK_SETUPHOLD: return(vpiSetupHold);

  case TCHK_FULLSKEW: return(vpiFullskew);
  case TCHK_RECREM: return(vpiRecrem);
  case TCHK_REMOVAL: return(vpiRemoval);
  case TCHK_TIMESKEW: return(vpiTimeskew);
  default: __vpi_terr(__FILE__, __LINE__);
 }
 return(vpiUndefined);
}
