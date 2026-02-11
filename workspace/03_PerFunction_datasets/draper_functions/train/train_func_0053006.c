self() {

  if (!_me) {
     if (KGlobal::hasMainComponent()) {
        KConfigGroup cfg(KGlobal::config(), "Socks");
        _me = new KSocks(&cfg);
     } else {
        _disabled = true;
        _me = new KSocks(0);
     }
  }
  return _me;
}
