mconf_set_new_config(bool new_config)
{
   DENTER(BASIS_LAYER, "mconf_set_new_config");
   SGE_LOCK(LOCK_MASTER_CONF, LOCK_WRITE);

   is_new_config = new_config;

   SGE_UNLOCK(LOCK_MASTER_CONF, LOCK_WRITE);
   DRETURN_VOID;
}
