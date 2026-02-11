addProperties(gem::Properties&props, int argc, t_atom*argv)
  {
    if(!argc)return;

    if(argv->a_type != A_SYMBOL) {
      ::error("no key given...");
      return;
    }
    std::string key=std::string(atom_getsymbol(argv)->s_name);
    std::vector<gem::any> values;
    argc--; argv++;
    while(argc-->0) {
      values.push_back(atom2any(argv++));
    }
    switch(values.size()) {
    default:
      props.set(key, values);
      break;
    case 1:
      props.set(key, values[0]);
      break;
    case 0:
      {
	gem::any dummy;
	props.set(key, dummy);
      }
      break;
    }
  }
