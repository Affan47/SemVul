_elm_config_save(void)
{
   char buf[4096], buf2[4096];
   int ok = 0, ret;
   const char *err;
   Eet_File *ef;
   size_t len;

   len = _elm_user_dir_snprintf(buf, sizeof(buf), "config/%s", _elm_profile);
   if (len + 1 >= sizeof(buf))
     return EINA_FALSE;

   ok = ecore_file_mkpath(buf);
   if (!ok)
     {
        ERR("Problem accessing Elementary's user configuration directory: %s",
            buf);
        return EINA_FALSE;
     }

   if (!_elm_config_profile_save())
     return EINA_FALSE;

   buf[len] = '/';
   len++;

   if (len + sizeof("base.cfg") >= sizeof(buf) - len)
     return EINA_FALSE;

   memcpy(buf + len, "base.cfg", sizeof("base.cfg"));
   len += sizeof("base.cfg") - 1;

   if (len + sizeof(".tmp") >= sizeof(buf))
     return EINA_FALSE;

   memcpy(buf2, buf, len);
   memcpy(buf2 + len, ".tmp", sizeof(".tmp"));

   ef = eet_open(buf2, EET_FILE_MODE_WRITE);
   if (!ef)
     return EINA_FALSE;

   ok = eet_data_write(ef, _config_edd, "config", _elm_config, 1);
   if (!ok)
     goto err;

   err = _elm_config_eet_close_error_get(ef, buf2);
   if (err)
     {
        ERR("%s", err);
        free((void *)err);
        goto err;
     }

   ret = ecore_file_mv(buf2, buf);
   if (!ret)
     {
        ERR("Error saving Elementary's configuration file");
        goto err;
     }

   ecore_file_unlink(buf2);
   return EINA_TRUE;

err:
   ecore_file_unlink(buf2);
   return EINA_FALSE;
}
