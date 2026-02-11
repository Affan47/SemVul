findOuterHandlerLabel(ExceptionGroup *eg)
#else
char * findOuterHandlerLabel(eg)
ExceptionGroup *eg;
#endif
{
  char              *label=NULL;
  ExceptionGroup    *outerEG;

  if (eg->forRule == 0) {
    if (eg->labelEntry != NULL) {
      outerEG=eg->labelEntry->outerEG;
      if (outerEG != NULL) {
        label=outerEG->altID;
        outerEG->used=1;
      };
    } else if (eg->outerEG != NULL) {
      outerEG=eg->outerEG;
      label=outerEG->altID;
      outerEG->used=1;
    };
  };
  return (label==NULL ? "" : label);
}
