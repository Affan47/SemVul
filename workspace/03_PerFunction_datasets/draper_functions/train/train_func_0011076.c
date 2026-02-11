map_state_and_process(DTR_ptr request){

    if(request->cancel_requested()) map_cancel_state(request);


    Arc::Time now;
    while((request->came_from_pre_processor() ||
           request->came_from_delivery() ||
           request->came_from_post_processor() ||
           request->came_from_generator()) &&
          request->get_process_time() <= now) {

      switch (request->get_status().GetStatus()) {
        case DTRStatus::NEW: ProcessDTRNEW(request); continue;
        case DTRStatus::CACHE_WAIT: ProcessDTRCACHE_WAIT(request); continue;
        case DTRStatus::CACHE_CHECKED: ProcessDTRCACHE_CHECKED(request); continue;
        case DTRStatus::RESOLVED: ProcessDTRRESOLVED(request); continue;
        case DTRStatus::REPLICA_QUERIED: ProcessDTRREPLICA_QUERIED(request); continue;
        case DTRStatus::PRE_CLEANED: ProcessDTRPRE_CLEANED(request); continue;
        case DTRStatus::STAGING_PREPARING_WAIT: ProcessDTRSTAGING_PREPARING_WAIT(request); continue;
        case DTRStatus::STAGED_PREPARED: ProcessDTRSTAGED_PREPARED(request); continue;
        case DTRStatus::TRANSFERRED: ProcessDTRTRANSFERRED(request); continue;
        case DTRStatus::REQUEST_RELEASED: ProcessDTRREQUEST_RELEASED(request); continue;
        case DTRStatus::REPLICA_REGISTERED: ProcessDTRREPLICA_REGISTERED(request); continue;
        case DTRStatus::CACHE_PROCESSED: ProcessDTRCACHE_PROCESSED(request); continue;
        default: break;
      }
    }

  }
