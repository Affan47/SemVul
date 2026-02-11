test_create_request(const char *requestStr, int count)
{
   lList *requests = NULL;
   char *request_cp = NULL;
   char *iter_dash = NULL;

   requests = lCreateList("requests", CE_Type);

   if (requests != NULL) {
       int i;
       for (i = 0; i < count; i++) {
          char *request_str;

          request_cp = strdup(requestStr);

          for (request_str = strtok_r(request_cp, " ", &iter_dash); request_str; request_str = strtok_r(NULL, " ", &iter_dash)) {
            lListElem *request = NULL;

            request = lCreateElem(CE_Type);

            if (request != NULL) {
               lSetString(request, CE_name, request_str);
               lSetString(request, CE_stringval, strtok_r(NULL, " ", &iter_dash));
            }
            else {
               lFreeList(&requests);
               goto end;
            }
            lAppendElem(requests, request);
          }
         if (request_cp != NULL) {
            free(request_cp);
            request_cp = NULL;
         }
       }
   }
end:
   if (request_cp != NULL) {
      free(request_cp);
      request_cp = NULL;
   }
   return requests;
}
