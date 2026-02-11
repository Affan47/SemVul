get_Vth()
{
  double v=initial_state;
  if(current) {
    try {
      current->get(v);
      if(digital && v >0.0)
	v = 5.0;
    }

    catch (Error *err) {
      if(err) {
	cout << "Warning stimulus: " << name() << " failed on: "<< err->toString() << endl;
	delete err;
      }
    }

  }
  return v;
}
