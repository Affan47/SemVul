ec2_set_flush_delay(sge_evc_class_t *thiz, int flush_delay)
{
   bool ret = false;
   sge_evc_t *sge_evc = (sge_evc_t *)thiz->sge_evc_handle;

   DENTER(EVC_LAYER, "ec2_set_flush_delay");

   if (sge_evc->ec == NULL) {
      ERROR((SGE_EVENT, MSG_EVENT_UNINITIALIZED_EC));
   } else {
      ret = (lGetUlong(sge_evc->ec, EV_flush_delay) != flush_delay) ? true : false;

      if (ret) {
         lSetUlong(sge_evc->ec, EV_flush_delay, flush_delay);
         ec2_config_changed(thiz);
      }
   }

   DRETURN(ret);
}
