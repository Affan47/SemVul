send(const char format[], ...) {

   va_list arg_list;
   char string[4096];

   ASSERT(format!=NULL);

   va_start(arg_list,format);
   vsprintf(string,format,arg_list);
   va_end(arg_list);

   fprintf(pipefd_e2a_1_stream,"%s\n",string);
}
