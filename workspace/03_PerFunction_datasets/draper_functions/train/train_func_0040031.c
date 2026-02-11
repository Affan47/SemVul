next(void) {
    while (true) {
      Space* n = e->next();
      unsigned long int i = stop->m_stat.restart;
      if (n != NULL) {
        NoGoods& ng = e->nogoods();
        ng.ng(0);
        master->constrain(*n);
        master->master(i,n,ng);
        stop->m_stat.nogood += ng.ng();
        stop->update(e->statistics());
        if (master->status(stop->m_stat) == SS_FAILED) {
          delete master;
          master = NULL;
          e->reset(NULL);
        } else {
          Space* slave = master;
          master = master->clone(shared);
          slave->slave(i,n);
          e->reset(slave);
        }
        return n;
      } else if (e->stopped() && stop->enginestopped()) {
        NoGoods& ng = e->nogoods();
        ng.ng(0);
        master->master(i,NULL,ng);
        stop->m_stat.nogood += ng.ng();
        long unsigned int nl = (*co)();
        stop->limit(e->statistics(),nl);
        if (master->status(stop->m_stat) == SS_FAILED)
          return NULL;
        Space* slave = master;
        master = master->clone(shared);
        slave->slave(i,n);
        e->reset(slave);
      } else {
        return NULL;
      }
    }
    GECODE_NEVER;
    return NULL;
  }
