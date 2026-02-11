detach() {
    omni_tracedmutex_lock sync(*vf_lock);

    if (vf_table) {
      omniORB::logs(25, "Release registered value factories.");

      for (CORBA::ULong i=0; i < vf_tablesize; i++) {

	ValueFactoryTableEntry *f, *n;
	ValueFactoryTableEntry** prev = &(vf_table[i]);

	for (f = vf_table[i]; f; f = n) {
	  n = f->next;

	  if (f->internal) {

	    prev = &(f->next);
	  }
	  else {
	    if (omniORB::trace(26)) {
	      omniORB::logger l;
	      l << "Release value factory for '" << f->repoId << "'.\n";
	    }
	    *prev = n;
	    f->factory->_remove_ref();
	    delete f;
	  }
	}
      }
    }
  }
}
