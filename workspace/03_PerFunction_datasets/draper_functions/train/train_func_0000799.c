rebind(const TranslationMap & trans) {
  _theFFZVertex = trans.translate(_theFFZVertex);
  _theFFPVertex = trans.translate(_theFFPVertex);
  _Z0           = trans.translate(_Z0);
  _gamma        = trans.translate(_gamma);
  HwMEBase::rebind(trans);
}
