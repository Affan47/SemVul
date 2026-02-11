Init() {

  static ClassDocumentation<alpha_s> documentation
    ("Base class for strong coupoling as used in matchbox");


  static Parameter<alpha_s,unsigned int> interfacemin_active_flavours
    ("min_active_flavours",
     "Minimum number of active flavours",
     &alpha_s::min_active_flavours_, 3, 0, 6,
     true, false, Interface::limited);

  static Parameter<alpha_s,unsigned int> interfacemax_active_flavours
    ("max_active_flavours",
     "Maximum number of active flavours",
     &alpha_s::max_active_flavours_, 6, 0, 6,
     true, false, Interface::limited);


  static Parameter<alpha_s,double> interfaceinput_alpha_s
    ("input_alpha_s",
     "alpha_s value at input scale",
     &alpha_s::alpha_s_in_, .1176, 0.0, 1.0,
     true, false, Interface::limited);


  static Parameter<alpha_s,Energy> interfaceinput_scale
    ("input_scale",
     "Input scale for alpha_s value",
     &alpha_s::scale_in_, GeV, 91.1876*GeV, 0.*GeV, 0.*GeV,
     true, false, Interface::lowerlim);


  static Command<alpha_s> interfacecheck
    ("check",
     "check",
     &alpha_s::check, false);

  static Parameter<alpha_s,double> interfacescale_factor
    ("scale_factor",
     "scale factor for argument",
     &alpha_s::scale_factor_, 1., 0.0, 100.0,
     true, false, Interface::limited);


  static Switch<alpha_s,bool> interfacefixed
    ("fixed",
     "",
     &alpha_s::fixed_, false, false, false);
  static SwitchOption interfacefixedOn
    (interfacefixed,
     "On",
     "",
     true);
  static SwitchOption interfacefixedOff
    (interfacefixed,
     "Off",
     "",
     false);

}
