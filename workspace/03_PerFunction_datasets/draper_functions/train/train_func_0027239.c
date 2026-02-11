run(const GMConfig& config,const Arc::User& user,const char* jobid,const std::string& args,Arc::Run** ere,bool su,bool job_proxy,RunPlugin* cred,RunPlugin::substitute_t subst,void* subst_arg) {
  *ere=NULL;
  Arc::Run* re = new Arc::Run(args);
  if((!re) || (!(*re))) {
    if(re) delete re;
    logger.msg(Arc::ERROR,"%s: Failure creating slot for child process",jobid?jobid:"");
    return false;
  };
  if(kicker_func_) re->AssignKicker(kicker_func_,kicker_arg_);
  RunParallel* rp = new RunParallel(config,user,jobid,su,job_proxy,cred,subst,subst_arg);
  if((!rp) || (!(*rp))) {
    if(rp) delete rp;
    delete re;
    logger.msg(Arc::ERROR,"%s: Failure creating data storage for child process",jobid?jobid:"");
    return false;
  };
  re->AssignInitializer(&initializer,rp);
  if(!re->Start()) {
    delete rp;
    delete re;
    logger.msg(Arc::ERROR,"%s: Failure starting child process",jobid?jobid:"");
    return false;
  };
  delete rp;
  *ere=re;
  return true;
}
