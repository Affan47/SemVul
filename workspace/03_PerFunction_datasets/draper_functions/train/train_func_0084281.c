sge_gdi_ctx_class_is_alive(sge_gdi_ctx_class_t *thiz)
{
   cl_com_SIRM_t* status = NULL;
   int cl_ret = CL_RETVAL_OK;
   cl_com_handle_t *handle = thiz->get_com_handle(thiz);


   const char* comp_name = prognames[QMASTER];
   const char* comp_host = thiz->get_master(thiz, false);
   int         comp_id   = 1;
   int         comp_port = thiz->get_sge_qmaster_port(thiz);

   DENTER(TOP_LAYER, "sge_gdi_ctx_class_is_alive");

   if (handle == NULL) {
      sge_gdi_ctx_class_error(thiz, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR,
                "handle not found %s:0", thiz->get_component_name(thiz));
      DRETURN(CL_RETVAL_PARAMS);
   }


   cl_com_append_known_endpoint_from_name((char*)comp_host, (char*)comp_name, comp_id,
                                          comp_port, CL_CM_AC_DISABLED, CL_TRUE);

   DPRINTF(("to->comp_host, to->comp_name, to->comp_id: %s/%s/%d\n", comp_host?comp_host:"", comp_name?comp_name:"", comp_id));
   cl_ret = cl_commlib_get_endpoint_status(handle, (char*)comp_host, (char*)comp_name, comp_id, &status);
   if (cl_ret != CL_RETVAL_OK) {
      sge_gdi_ctx_class_error(thiz, STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR,
                "cl_commlib_get_endpoint_status failed: "SFQ, cl_get_error_text(cl_ret));
   } else {
      DEBUG((SGE_EVENT,MSG_GDI_QMASTER_STILL_RUNNING));
   }

   if (status != NULL) {
      DEBUG((SGE_EVENT,MSG_GDI_ENDPOINT_UPTIME_UU, sge_u32c(status->runtime) ,
             sge_u32c(status->application_status)));
      cl_com_free_sirm_message(&status);
   }

   DRETURN(cl_ret);
}
