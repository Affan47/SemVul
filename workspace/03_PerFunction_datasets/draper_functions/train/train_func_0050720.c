_Cthread_addspec(file, line, Cspec_new)
     char *file;
     int line;
     struct Cspec_element_t *Cspec_new;
{
  struct Cspec_element_t *current = &Cspec;

#ifdef CTHREAD_DEBUG
  if (file != NULL) {
    if (Cthread_debug != 0)
      log(LOG_INFO,"[Cthread    [%2d]] In _Cthread_addspec(0x%lx) called at/behind %s:%d\n",_Cthread_self(),
          (unsigned long) Cspec_new,file,line);
  }
#endif

  if (_Cthread_obtain_mtx(file,line,&(Cthread.mtx),-1))
    return(-1);


  while (current->next != NULL) {
    current = current->next;
  }


  current->next = Cspec_new;


  ((struct Cspec_element_t *) current->next)->next = NULL;

  _Cthread_release_mtx(file,line,&(Cthread.mtx));

  return(0);
}
