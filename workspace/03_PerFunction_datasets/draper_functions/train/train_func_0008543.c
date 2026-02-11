_elm_dangerous_call_check(const char *call)
{
   char buf[256];
   const char *eval;

   snprintf(buf, sizeof(buf), "%i.%i.%i.%i", VMAJ, VMIN, VMIC, VREV);
   eval = getenv("ELM_NO_FINGER_WAGGLING");
   if ((eval) && (!strcmp(eval, buf)))
     return 0;
   printf("ELEMENTARY FINGER WAGGLE!!!!!!!!!!\n"
          "\n"
          "  %s() used.\n"
          "PLEASE see the API documentation for this function. This call\n"
          "should almost never be used. Only in very special cases.\n"
          "\n"
          "To remove this warning please set the environment variable:\n"
          "  ELM_NO_FINGER_WAGGLING\n"
          "To the value of the Elementary version + revision number. e.g.:\n"
          "  1.2.5.40295\n"
          "\n"
          ,
          call);
   return 1;
}
