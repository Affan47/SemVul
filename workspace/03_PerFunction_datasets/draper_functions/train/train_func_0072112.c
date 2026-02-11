ec2_get_id(sge_evc_class_t *thiz)
{
   sge_evc_t *sge_evc = (sge_evc_t *) thiz->sge_evc_handle;

   DENTER(EVC_LAYER, "ec2_get_id");
   if (sge_evc->ec == NULL) {
      ERROR((SGE_EVENT, MSG_EVENT_UNINITIALIZED_EC));
      DRETURN(EV_ID_INVALID);
   }

   DRETURN((ev_registration_id)lGetUlong(sge_evc->ec, EV_id));
}
