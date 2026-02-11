jgdi_report_resource_value(qhost_report_handler_t* handler, const char* dominance, const char* name, const char* value, lList** alpp)
{
   jgdi_report_handler_t* jgdi_handler = (jgdi_report_handler_t*)handler->ctx;
   JNIEnv *env = jgdi_handler->env;
   jstring value_obj = NULL;

   DENTER(JGDI_LAYER, "jgdi_report_resource_value");

   if (jgdi_handler->qhost_info == NULL) {
      answer_list_add(alpp, "jgdi_report_resource_value: qhost_info object not set", STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
      DRETURN(QHOST_ERROR);
   }

   value_obj = (*env)->NewStringUTF(env, value);

   if (HostInfoImpl_putResourceValue(env, jgdi_handler->qhost_info, dominance, name, value_obj, alpp) != JGDI_SUCCESS) {
     DRETURN(QHOST_ERROR);
   }

   DRETURN(QHOST_SUCCESS);
}
