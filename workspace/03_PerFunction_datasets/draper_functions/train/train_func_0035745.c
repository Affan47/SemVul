set_certificate(sge_gdi_ctx_class_t *thiz, const char *cert) {
   sge_gdi_ctx_t *es = (sge_gdi_ctx_t *) thiz->sge_gdi_ctx_handle;

   DENTER(BASIS_LAYER, "sge_gdi_ctx_class->set_certificate");

   if (es->ssl_certificate != NULL) {
      FREE(es->ssl_certificate);
   }
   es->ssl_certificate = cert ? strdup(cert) : NULL;

   DRETURN_VOID;
}
