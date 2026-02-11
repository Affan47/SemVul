job_get_env_string(const lListElem *job, const char *variable)
{
   const char *ret = NULL;
   DENTER(TOP_LAYER, "job_get_env_value");
   ret = var_list_get_string(lGetList(job, JB_env_list), variable);
   DRETURN(ret);
}
