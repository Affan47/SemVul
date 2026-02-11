BusyWait (DWORD msec)
{
   switch (DisplayStatus)
   {
      case DISPLAY_ERROR_TRAP:
      case DISPLAY_COMM_PROBLEM:
      case DISPLAY_PRINTER_NOT_SUPPORTED:
      case DISPLAY_OUT_OF_PAPER:
      case DISPLAY_PHOTOTRAY_MISMATCH:
      case DISPLAY_TOP_COVER_OPEN:
      case DISPLAY_NO_COLOR_PEN:
      case DISPLAY_NO_BLACK_PEN:
      case DISPLAY_NO_PENS:
         BUG("WARNING: printer bi-di error=%d\n", DisplayStatus);
         DisplayStatus = DISPLAY_PRINTING_CANCELED;
         return JOB_CANCELED;
      default:
         break;
   }
   return NO_ERROR;
}
