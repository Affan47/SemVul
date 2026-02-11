sweep()
{
  head(_start, _stop, "Freq");
  first();
  CARD_LIST::card_list.ac_begin();
  do {
    _sim->_jomega = COMPLEX(0., _sim->_freq * M_TWO_PI);
    solve();
    outdata(_sim->_freq);
  } while (next());
}
