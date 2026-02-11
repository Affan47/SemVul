glp_open_tee(const char *name)
{     ENV *env = get_env_ptr();
      if (env->tee_file != NULL)
      {
         return 1;
      }
      env->tee_file = fopen(name, "w");
      if (env->tee_file == NULL)
      {
         return 2;
      }
      return 0;
}
