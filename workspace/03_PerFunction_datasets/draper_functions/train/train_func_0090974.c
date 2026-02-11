progressCallback(void * ,
  T_DIMSE_StoreProgress *progress,
  T_DIMSE_C_StoreRQ * req)
{
  if (progress->state == DIMSE_StoreBegin)
  {
    OFString str;
    OFLOG_DEBUG(storescuLogger, DIMSE_dumpMessage(str, *req, DIMSE_OUTGOING));
  }


  OFLogger progressLogger = OFLog::getLogger("dcmtk.apps." OFFIS_CONSOLE_APPLICATION ".progress");
  if (progressLogger.getChainedLogLevel() == OFLogger::INFO_LOG_LEVEL) {
    switch (progress->state) {
      case DIMSE_StoreBegin:
        COUT << "XMIT: "; break;
      case DIMSE_StoreEnd:
        COUT << OFendl; break;
      default:
        COUT << "."; break;
    }
    COUT.flush();
  }
}
