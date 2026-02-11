ec2_get_flush_delay(sge_evc_class_t *thiz)
{
   int flush_delay = 0;
   sge_evc_t *sge_evc = (sge_evc_t *)thiz->sge_evc_handle;

   DENTER(EVC_LAYER, "ec2_get_flush_delay");

   if (sge_evc->ec == NULL) {
      ERROR((SGE_EVENT, MSG_EVENT_UNINITIALIZED_EC));
   } else {
      flush_delay = lGetUlong(sge_evc->ec, EV_flush_delay);
   }

   DRETURN(flush_delay);
}
