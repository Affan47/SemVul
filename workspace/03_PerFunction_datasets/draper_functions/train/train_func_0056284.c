get_state_name() const {
  if((job_state<0) || (job_state>=JOB_STATE_NUM))
                       return state_names[JOB_STATE_UNDEFINED];
  return state_names[job_state];
}
