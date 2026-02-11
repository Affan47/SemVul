dump_all_do (int slot)
{
  int rc, i, j;
  unsigned char *buffer;
  size_t buflen;

  for (i=0; data_objects[i].tag; i++)
    {
      if (data_objects[i].get_from)
        continue;


      rc = iso7816_get_data (slot, 0, data_objects[i].tag, &buffer, &buflen);
      if (gpg_err_code (rc) == GPG_ERR_NO_OBJ)
        ;
      else if (rc)
        log_info ("DO `%s' not available: %s\n",
                  data_objects[i].desc, gpg_strerror (rc));
      else
        {
          if (data_objects[i].binary)
            {
              log_info ("DO `%s': ", data_objects[i].desc);
              log_printhex ("", buffer, buflen);
            }
          else
            log_info ("DO `%s': `%.*s'\n",
                      data_objects[i].desc,
                      (int)buflen, buffer);

          if (data_objects[i].constructed)
            {
              for (j=0; data_objects[j].tag; j++)
                {
                  const unsigned char *value;
                  size_t valuelen;

                  if (j==i || data_objects[i].tag != data_objects[j].get_from)
                    continue;
                  value = find_tlv_unchecked (buffer, buflen,
                                              data_objects[j].tag, &valuelen);
                  if (!value)
                    ;
                  else if (valuelen > buflen - (value - buffer))
                    log_error ("warning: constructed DO too short\n");
                  else
                    {
                      if (data_objects[j].binary)
                        {
                          log_info ("DO `%s': ", data_objects[j].desc);
                          if (valuelen > 200)
                            log_info ("[%u]\n", (unsigned int)valuelen);
                          else
                            log_printhex ("", value, valuelen);
                        }
                      else
                        log_info ("DO `%s': `%.*s'\n",
                                  data_objects[j].desc,
                                  (int)valuelen, value);
                    }
                }
            }
        }
      xfree (buffer); buffer = NULL;
    }
}
