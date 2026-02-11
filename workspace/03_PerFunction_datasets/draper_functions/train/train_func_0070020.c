GENLIB_PUSH()
{
  eStack_t *pNew;


  pNew = (eStack_t*)malloc(sizeof(eStack_t));

  if (pNew == NULL) {
    eprinth(NULL);
    eprints("GENLIB_PUSH: Cannot allocate new stack element.\n");
    EXIT(1);
  }

  pNew->WORK_LOFIG = WORK_LOFIG;
  pNew->WORK_PHFIG = WORK_PHFIG;
  pNew->WORK_PHINS = WORK_PHINS;
  pNew->num_index  = num_index;
  pNew->Prev       = genlibStack;

  WORK_LOFIG = NULL;
  WORK_PHFIG = NULL;
}
