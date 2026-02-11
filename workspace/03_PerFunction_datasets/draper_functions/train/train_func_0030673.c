node_is_connected(int i)const {
    switch (i) {
    case 0:  return _output_label != "";
    case 1:  return _input_label != "";
    default: unreachable(); return false;
    }
  }
