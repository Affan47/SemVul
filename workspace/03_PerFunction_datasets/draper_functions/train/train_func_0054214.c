glp_init_env(void)
{     ENV *env;
      int ok;

      ok = (CHAR_BIT == 8 && sizeof(char) == 1 &&
         sizeof(short) == 2 && sizeof(int) == 4 &&
         (sizeof(void *) == 4 || sizeof(void *) == 8));
      if (!ok)
         return 3;

      if (tls_get_ptr() != NULL)
         return 1;

      env = malloc(sizeof(ENV));
      if (env == NULL)
         return 2;
      memset(env, 0, sizeof(ENV));
      sprintf(env->version, "%d.%d",
         GLP_MAJOR_VERSION, GLP_MINOR_VERSION);
      env->self = env;
      env->term_buf = malloc(TBUF_SIZE);
      if (env->term_buf == NULL)
      {  free(env);
         return 2;
      }
      env->term_out = GLP_ON;
      env->term_hook = NULL;
      env->term_info = NULL;
      env->tee_file = NULL;
      env->err_file = NULL;
      env->err_line = 0;
      env->err_hook = NULL;
      env->err_info = NULL;
      env->mem_limit = SIZE_T_MAX;
      env->mem_ptr = NULL;
      env->mem_count = env->mem_cpeak = 0;
      env->mem_total = env->mem_tpeak = 0;
      env->h_odbc = env->h_mysql = NULL;

      tls_set_ptr(env);

      return 0;
}
