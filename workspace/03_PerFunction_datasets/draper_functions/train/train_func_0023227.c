GRSThtcpTSTrequestMake(char **request, int *request_length,
                           unsigned int trans_id,
                           char *method, char *uri, char *req_hdrs)


{
   if ((method == NULL) || (uri == NULL) || (req_hdrs == NULL))
                                               return GRST_RET_FAILED;

   *request_length =
     asprintf(request,"%c%c"
                      "%c%c"
                      "%c%c"
                      "%c%c"
                      "%c%c%c%c"
                      "%c%c%s"
                      "%c%c%s"
                      "%c%c%s"
                      "%c%c%s"
                      "%c%c",
                     0, 0,
                     0, 0,
                     0, 0,
                     GRSThtcpTSTop * 16, 2,
                     0, 0, 0, 0,
                     strlen(method) / 256, strlen(method) % 256, method,
                     strlen(uri)    / 256, strlen(uri) % 256,    uri,
                     0,                    8,                    "HTTP/1.1",
                     strlen(req_hdrs)/256, strlen(req_hdrs) % 256, req_hdrs,
                     0, 2);

   if (*request_length < 0) return GRST_RET_FAILED;

   (*request)[0] = *request_length / 256;
   (*request)[1] = *request_length % 256;

   (*request)[4] = (*request_length - 6) / 256;
   (*request)[5] = (*request_length - 6) % 256;

   memcpy(&((*request)[8]), &trans_id, 4);

   return GRST_RET_OK;
}
