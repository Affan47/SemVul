StartProvidingService()


{
  OFCondition cond;


  cond = dataSource->ConnectToDataSource();
  if( cond.bad() )
  {

    OFLOG_ERROR(wlmscpfsLogger, cond.text());


    return( 1 );
  }


  WlmActivityManager *activityManager = new WlmActivityManager(
      dataSource, opt_port,
      opt_refuseAssociation,
      opt_rejectWithoutImplementationUID,
      opt_sleepAfterFind, opt_sleepDuringFind,
      opt_maxPDU, opt_networkTransferSyntax,
      opt_failInvalidQuery,
      opt_singleProcess, opt_maxAssociations,
      opt_blockMode, opt_dimse_timeout, opt_acse_timeout,
      opt_forkedChild, command_argc, command_argv );
  cond = activityManager->StartProvidingService();
  if( cond.bad() )
  {

    OFLOG_ERROR(wlmscpfsLogger, cond.text());


    dataSource->DisconnectFromDataSource();


    delete activityManager;


    return( 1 );
  }


  delete activityManager;


  cond = dataSource->DisconnectFromDataSource();
  if( cond.bad() )
  {

    OFLOG_ERROR(wlmscpfsLogger, cond.text());


    return( 1 );
  }


  return( 0 );
}
