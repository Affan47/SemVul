set_default_max ( XmpSpinboxWidget cw )
{
   switch ( SpinboxType(cw) ) {
      case XmSPINBOX_CLOCK_HM : SpinboxMaxValue(cw) = 24*60-1; break;
      case XmSPINBOX_CLOCK_HMS : SpinboxMaxValue(cw) = 24*60*60-1; break;
      case XmSPINBOX_CLOCK_DHMS : SpinboxMaxValue(cw) = 365*24*60*60-1; break;
      case XmSPINBOX_BEACONCODE : SpinboxMaxValue(cw) = 010000-1; break;
      case XmSPINBOX_DOLLARS : SpinboxMaxValue(cw) = LONG_MAX-1; break;
      case XmSPINBOX_STRINGS : SpinboxMaxValue(cw) = SpinboxItemCount(cw)-1; break;
      case XmSPINBOX_USER_DEFINED : break;
      case XmSPINBOX_NUMBER : SpinboxMaxValue(cw) = LONG_MAX-1; break;
      default : assert ( 0 ); break;
   }
}
