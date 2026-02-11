fftallocate()
{
  int probes = printlist().size();
  _fdata = new COMPLEX*[probes];
  for (int ii = 0;  ii < probes;  ++ii) {
    _fdata[ii] = new COMPLEX[_timesteps+100];
  }
}
