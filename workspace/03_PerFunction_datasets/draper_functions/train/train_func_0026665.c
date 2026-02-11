LogStats(ConfServer *pCS)
{
   u_int TxBytes = TxBytesAllConf;
   u_int TxMBytes = TxMBytesAllConf;
   u_int RxBytes = RxBytesAllConf;
   u_int RxMBytes = RxMBytesAllConf;

   CalcBW(pCS,FALSE);

   if(TxBytes > 1000000) {
      TxMBytes += TxBytes / 1000000;
      TxBytes %= 1000000;
   }

   if(RxBytes > 1000000) {
      RxMBytes += RxBytes / 1000000;
      RxBytes %= 1000000;
   }

   LOG_NORM(("Users:%d BW T:%d R:%d T:%d.%02dMB R:%d.%02dMB Up:%s\n",
             ConferenceClients,pCS->TxBandWidth,pCS->RxBandWidth,
             TxMBytes,TxBytes*100/1000000,RxMBytes,RxBytes*100/1000000,
             TimeLapse2String(BootTime,TRUE)));
}
