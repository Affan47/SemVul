pollReferenceThreads() {

    ZTDEBUG("pollReferenceThreads()\n");

    for(ThreadList::iterator i = _referenceThreads.begin(); i != _referenceThreads.end(); ++i) {

      ThreadImpl* impl = (ThreadImpl*)*i;
      impl->delReference();

      ZTDEBUG("1 reference-thread reclaimed.\n");

    }

  }
