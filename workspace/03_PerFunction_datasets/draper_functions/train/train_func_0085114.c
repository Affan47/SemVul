submit_batch()
  {
    std::string urstr;
    usagerecordset.GetDoc(urstr,false);

    logger.msg(Arc::INFO,
               "Logging UR set of %d URs.",
               urn);
    logger.msg(Arc::DEBUG,
               "UR set dump: %s",
               urstr.c_str());


    Arc::MCC_Status status=send_request(urstr);

    if (status.isOk())
      {

        aggregationManager->save_records();

        aggregationManager->Reporting_records();


        for (std::list<JobLogFile>::iterator jp=joblogs.begin();
             jp!=joblogs.end();
             jp++
             )
          {
            (*jp).remove();
          }
        clear();
        return 0;
      }
    else
      {
        logger.msg(Arc::ERROR,
                   "%s: %s",
                   status.getOrigin().c_str(),
                   status.getExplanation().c_str()
                   );
        clear();
        return -1;
      }
  }
