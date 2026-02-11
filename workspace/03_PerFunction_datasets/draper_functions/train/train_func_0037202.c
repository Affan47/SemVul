pp_open(mud_device *pd)
{
   char dev[255], uriModel[128], model[128];
   int len, m, fd;
   enum HPMUD_RESULT stat = HPMUD_R_IO_ERROR;

   pthread_mutex_lock(&pd->mutex);

   hpmud_get_uri_model(pd->uri, uriModel, sizeof(uriModel));

   if (pd->id[0] == 0)
   {

      hpmud_get_uri_datalink(pd->uri, dev, sizeof(dev));
      if ((fd = open(dev, O_RDWR | O_NOCTTY)) < 0)
      {
         BUG("unable to open %s: %m\n", pd->uri);
         goto bugout;
      }


      if (ioctl(fd, PPGETMODES, &m))
      {
         BUG("unable to open %s: %m\n", pd->uri);
         goto bugout;
      }


      if (claim_pp(fd))
         goto bugout;

      len = device_id(fd, pd->id, sizeof(pd->id));

      if (len > 0 && is_hp(pd->id))
         power_up(pd, fd);

      release_pp(fd);

      if (len == 0)
         goto bugout;

      pd->open_fd = fd;
   }


   hpmud_get_model(pd->id, model, sizeof(model));
   if (strcmp(uriModel, model) != 0)
   {
      stat = HPMUD_R_INVALID_DEVICE_NODE;
      BUG("invalid model %s != %s\n", uriModel, model);
      goto bugout;
   }

   stat = HPMUD_R_OK;

bugout:
   pthread_mutex_unlock(&pd->mutex);
   return stat;
}
