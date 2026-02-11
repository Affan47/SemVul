detach_stimulus(stimulus *s)
{
  stimulus *sptr;


  if(!s)
    return;

  if(stimuli) {
    if(s == stimuli) {


      stimuli = s->next;
      s->detach(this);
      nStimuli--;

    } else {

      sptr = stimuli;

      do {
        if(s == sptr->next) {

          sptr->next = s->next;
          s->detach(this);
          nStimuli--;

          return;
        }

        sptr = sptr->next;
      } while(sptr);

    }
  }
}
