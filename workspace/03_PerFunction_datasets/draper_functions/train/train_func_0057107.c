buildRequestList(int n)
{
   lList *requestlist = NULL;
   lListElem *request;

   requestlist = lCreateList("requestlist", JobRequestT);

   request = lCreateElem(JobRequestT);
   lSetString(request, R_name, "ARCH");
   lSetString(request, R_operator, "==");
   lSetString(request, R_value, "irix");
   lAppendElem(requestlist, request);

   if (n) {
      request = lCreateElem(JobRequestT);
      lSetString(request, R_name, "editor");
      lSetString(request, R_operator, "==");
      lSetString(request, R_value, "vi");
      lAppendElem(requestlist, request);
   }

   request = lCreateElem(JobRequestT);
   lSetString(request, R_name, "GROUP");
   lSetString(request, R_operator, "==");
   lSetString(request, R_value, "graphic");
   lAppendElem(requestlist, request);

   return requestlist;
}
