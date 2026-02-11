current_port_value(int i)const {
    switch (i) {
    case 0:  return _output_label;
    case 1:  return _input_label;
    default: unreachable(); return COMPONENT::current_port_value(i);
    }
  }
