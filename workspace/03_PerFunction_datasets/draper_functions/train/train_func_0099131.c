process(void)
{
  DBC_CHECK(static_cast<int>(num_of_samples.size()) == channels());

  int res = pthread_mutex_trylock(&lock_rep);
  if (res == 0) {
    i.begin();
    while(!i.end()) {

      DBC_CHECK(num_of_samples.size() > static_cast<unsigned>(i.channel()));
      num_of_samples[i.channel()]++;

      if (*i.current() >= 0) {
	if (*i.current() > max_pos) max_pos = *i.current();

	for(unsigned j = 0; j < pos_samples_db.size(); j++) {
	  if (*i.current() > bucket_table[j].threshold) {
	    pos_samples_db[j][i.channel()]++;
	    break;
	  }
	}
      }
      else {
	if (-(*i.current()) > max_neg) max_neg = -(*i.current());

	for(unsigned j = 0; j < neg_samples_db.size(); j++) {
	  if (*i.current() < -bucket_table[j].threshold) {
	    neg_samples_db[j][i.channel()]++;
	    break;
	  }
	}
      }
      i.next();
    }

    res = pthread_mutex_unlock(&lock_rep);
    DBC_CHECK(res == 0);
  }

}
