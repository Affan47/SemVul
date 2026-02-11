on_gettextpo_xerror2 (int severity, po_message_t , const char * filename1, size_t , size_t ,
  int , const char *message_text1,
  po_message_t , const char * , size_t , size_t ,
  int , const char * )
{
  show_gettext_error(severity, filename1, message_text1);

  #ifdef PO_SEVERITY_FATAL_ERROR
  if(severity == PO_SEVERITY_FATAL_ERROR)
    longjmp(jump, 1);
  #endif
}
