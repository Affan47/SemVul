setConfig(const KConfigGroup *config)
{


  if (_me && _disabled) {
     delete _me;
     _me = 0;
     _disabled = false;
  }
  if (!_me)
    _me = new KSocks(config);
}
