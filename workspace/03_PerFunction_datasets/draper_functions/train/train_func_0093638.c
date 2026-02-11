_e_config_profile_name_get(Eet_File *ef)
{

   char *data;
   const char *s = NULL;
   int data_len = 0;

   data = eet_read(ef, "config", &data_len);
   if ((data) && (data_len > 0))
     {
        int ok = 1;

        for (s = data; s < (data + data_len); s++)
          {


             if ((*s < ' ') || (*s > '~') || (*s == '/'))
               {
                  ok = 0;
                  break;
               }
          }
        s = NULL;
        if (ok)
          s = eina_stringshare_add_length(data, data_len);
        free(data);
     }
   return s;
}
