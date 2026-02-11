ac_probe_ext(const std::string& x)const
{
  COMPLEX admittance = (is_source()) ? _loss0 : _acg+_loss0;

  if (Umatch(x, "v{out} ")) {
    return XPROBE(ac_outvolts());
  }else if (Umatch(x, "vin ")) {
    return XPROBE(ac_involts());
  }else if (Umatch(x, "i ")) {
    return XPROBE(ac_amps());
  }else if (Umatch(x, "p ")) {
    return XPROBE(ac_outvolts() * conj(ac_amps()), mtREAL, 10.);
  }else if (Umatch(x, "nv ")) {untested();
    return XPROBE(value());
  }else if (Umatch(x, "ev ")) {
    return XPROBE(_ev);
  }else if (Umatch(x, "y ")) {untested();
    return XPROBE(admittance, mtREAL);
  }else if (Umatch(x, "r ")) {
    if (admittance == 0.) {untested();
      return XPROBE(MAXDBL);
    }else{untested();
      return XPROBE(1. / admittance);
    }
  }else if (Umatch(x, "z ")) {
    return XPROBE(port_impedance(_n[OUT1], _n[OUT2], _sim->_acx, mfactor()*admittance));
  }else if (Umatch(x, "zraw ")) {
    return XPROBE(port_impedance(_n[OUT1], _n[OUT2], _sim->_acx, COMPLEX(0.)));
  }else{
    return COMPONENT::ac_probe_ext(x);
  }
}
