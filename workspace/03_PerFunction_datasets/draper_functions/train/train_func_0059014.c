clean_conf(void) {

   DENTER(BASIS_LAYER, "clean_conf");

   FREE(Master_Config.execd_spool_dir);
   FREE(Master_Config.mailer);
   FREE(Master_Config.xterm);
   FREE(Master_Config.load_sensor);
   FREE(Master_Config.prolog);
   FREE(Master_Config.epilog);
   FREE(Master_Config.shell_start_mode);
   FREE(Master_Config.login_shells);
   FREE(Master_Config.enforce_project);
   FREE(Master_Config.enforce_user);
   FREE(Master_Config.administrator_mail);
   lFreeList(&Master_Config.user_lists);
   lFreeList(&Master_Config.xuser_lists);
   lFreeList(&Master_Config.projects);
   lFreeList(&Master_Config.xprojects);
   FREE(Master_Config.set_token_cmd);
   FREE(Master_Config.pag_cmd);
   FREE(Master_Config.shepherd_cmd);
   FREE(Master_Config.qmaster_params);
   FREE(Master_Config.execd_params);
   FREE(Master_Config.reporting_params);
   FREE(Master_Config.gid_range);
   FREE(Master_Config.qlogin_daemon);
   FREE(Master_Config.qlogin_command);
   FREE(Master_Config.rsh_daemon);
   FREE(Master_Config.rsh_command);
   FREE(Master_Config.jsv_url);
   FREE(Master_Config.jsv_allowed_mod);
   FREE(Master_Config.rlogin_daemon);
   FREE(Master_Config.rlogin_command);
   FREE(Master_Config.auto_user_default_project);
   FREE(Master_Config.delegated_file_staging);
   FREE(Master_Config.libjvm_path);
   FREE(Master_Config.additional_jvm_args);

   memset(&Master_Config, 0, sizeof(sge_conf_type));

   DRETURN_VOID;
}
