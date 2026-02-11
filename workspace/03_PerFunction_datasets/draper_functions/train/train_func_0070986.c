process(void)
{
  long int len = dtime * dnum;

  i.begin();
  while(!i.end()) {
    for(int n = 0; n < channels(); n++) {
      SAMPLE_SPECS::sample_t temp1 = 0.0;
      for(int nm2 = 0; nm2 < dnum; nm2++) {
	if (filled[n][nm2] == true) {
	  DBC_CHECK((delay_index[n] + nm2 * dtime) % len >= 0);
	  DBC_CHECK((delay_index[n] + nm2 * dtime) % len < len);
	  temp1 += buffer[n][(delay_index[n] + nm2 * dtime) % len];
	}
      }
      buffer[n][delay_index[n]] = *i.current(n);
      *i.current(n) = (*i.current(n) * (1.0 - mix)) + (temp1 * mix / dnum);

      --(delay_index[n]);
      for(int nm2 = 0; nm2 < dnum; nm2++) {
	if (delay_index[n] < len - dtime * nm2) filled[n][nm2] = true;
      }
      if (delay_index[n] == -1) delay_index[n] = len - 1;
    }
    i.next();
  }
}
