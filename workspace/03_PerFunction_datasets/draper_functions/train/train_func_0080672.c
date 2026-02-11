assign(const splinefield& inf)
{
  _sp = inf._sp;
  for (unsigned int i=0; i<3; i++) {
    _dsp[i] = boost::shared_ptr<Spline3D<double> >(new Spline3D<double>(*(inf._dsp[i])));
  }
}
