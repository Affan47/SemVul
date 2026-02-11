ESWipeActivity(ARexGMConfig& config,Arc::XMLNode in,Arc::XMLNode out) {


  Arc::XMLNode id = in["ActivityID"];
  unsigned int n = 0;
  for(;(bool)id;++id) {
    if((++n) > MAX_ACTIVITIES) {
       Arc::SOAPFault fault(out.Parent(),Arc::SOAPFault::Sender,"");
      ESVectorLimitExceededFault(fault,MAX_ACTIVITIES,"Too many ActivityID");
      out.Destroy();
      return Arc::MCC_Status(Arc::STATUS_OK);
    };
  };
  id = in["ActivityID"];
  for(;(bool)id;++id) {
    std::string jobid = id;
    Arc::XMLNode item = out.NewChild("esmanag:WipeActivityResponseItem");
    item.NewChild("estypes:ActivityID") = jobid;
    ARexJob job(jobid,config,logger_);
    if(!job) {

      logger_.msg(Arc::ERROR, "EMIES:WipeActivity: job %s - %s", jobid, job.Failure());
      ESActivityNotFoundFault(item.NewChild("dummy"),job.Failure());
    } else {
      if((job.State() != "FINISHED") &&
         (job.State() != "DELETED")) {
        logger_.msg(Arc::ERROR, "EMIES:WipeActivity: job %s - state is %s, not terminal", jobid, job.State());
        ESOperationNotAllowedFault(item.NewChild("dummy"),"Not in terminal state");
      } else if(!job.Clean()) {

        logger_.msg(Arc::ERROR, "EMIES:WipeActivity: job %s - %s", jobid, job.Failure());

        ESOperationNotAllowedFault(item.NewChild("dummy"),job.Failure());
      } else {
        item.NewChild("esmanag:EstimatedTime") = Arc::tostring(config.GmConfig().WakeupPeriod());
      };
    };
  };
  return Arc::MCC_Status(Arc::STATUS_OK);
}
