set_scon(bool value)
{
  if (_scon == value)
    return;

  DBG(2, form("KCemu/Poly880/set_scon",
              "Poly880::set_scon(): value = %d%s\n",
              value,
	      _scon ? "" : " - NMI Flip-Flop reset"));

  if (!_scon)
    _nmi_flip_flop = false;

  _scon = value;
}
