quantize(trackno, xunit)


int trackno, xunit;
{
  struct listx* j;
  struct anote* this;
  int spare;
  int toterror;
  int quantum;
  int posnum,xxnum;


  if (xunit == 0) {
    return(10000);
  };
  quantum = (int) (2.*xunit/parts_per_unitlen);
  track[trackno].startunits = (2*(track[trackno].startwait + (quantum/4)))/quantum;
  spare = 0;
  toterror = 0;
  j = track[trackno].head;
  posnum = 0;
  while (j != NULL) {
    this = j->note;


    this->xnum = (2*(this->dtnext + spare + (quantum/4)))/quantum;
    this->playnum = (2*(this->tplay + (quantum/4)))/quantum;
    if ((this->playnum == 0) && (keep_short)) {
      this->playnum = 1;
    };


    xxnum =  xnum_to_next_nonchordal_note(j,spare,quantum);
    if ((swallow_rests>=0) && (xxnum - this->playnum <= restsize)
		        && xxnum > 0) {
      this->playnum = xxnum;
    };

    spare = spare + this->dtnext - (this->xnum*xunit/parts_per_unitlen);
    if (spare > 0) {
      toterror = toterror + spare;
    }
    else {
      toterror = toterror - spare;
    };


    spare = (spare * 96)/100;
    this->posnum = posnum;
    posnum += this->xnum;
    j = j->next;
  };
  return(toterror);
}
