ec2_set_session(sge_evc_class_t *thiz, const char *session)
{
   bool ret = false;
   sge_evc_t *sge_evc = (sge_evc_t *) thiz->sge_evc_handle;

   DENTER(EVC_LAYER, "ec2_set_session");

   if (sge_evc->ec == NULL) {
      ERROR((SGE_EVENT, MSG_EVENT_UNINITIALIZED_EC));
   } else {
      lSetString(sge_evc->ec, EV_session, session);


      ec2_config_changed(thiz);
      ret = true;
   }

   DRETURN(ret);
}
