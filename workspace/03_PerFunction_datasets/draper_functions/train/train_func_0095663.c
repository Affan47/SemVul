add(const char* state,const char* options,const char* command) {
  job_state_t i = GMJob::get_state(state);
  if(i != JOB_STATE_UNDEFINED) {
    return add(i,options,command);
  };
  return false;
}
