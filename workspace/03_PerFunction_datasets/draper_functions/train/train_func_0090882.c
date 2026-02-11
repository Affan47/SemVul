bootstrap_state_destroy(sge_bootstrap_state_t* theState)
{
   FREE(theState->admin_user);
   FREE(theState->default_domain);
   FREE(theState->spooling_method);
   FREE(theState->spooling_lib);
   FREE(theState->spooling_params);
   FREE(theState->binary_path);
   FREE(theState->qmaster_spool_dir);
   FREE(theState->security_mode);
   free(theState);
}
