lpm_mux(Design*des, NetMux*obj)
{
      if (obj->size() != 2)
	    return;
      if (obj->sel_width() != 1)
	    return;

#if 0


      if (obj->pin_Data(0).nexus()->drivers_constant() &&
          obj->pin_Data(0).nexus()->driven_value() == verinum::Vz) {
	    replace_with_mos(des, obj, NetLogic::NMOS);
	    count += 1;
	    return;
      }


      if (obj->pin_Data(1).nexus()->drivers_constant() &&
          obj->pin_Data(1).nexus()->driven_value() == verinum::Vz) {
	    replace_with_mos(des, obj, NetLogic::PMOS);
	    count += 1;
	    return;
      }
#endif


      bool flag = obj->pin_Sel().nexus()->drivers_constant();


      flag &= !obj->pin_Sel().nexus()->assign_lval();

      verinum::V sel_val = flag? obj->pin_Sel().nexus()->driven_value() : verinum::Vx;
      if ((sel_val != verinum::Vz) && (sel_val != verinum::Vx)) {
	    NetBUFZ*tmp = new NetBUFZ(obj->scope(), obj->name(), obj->width());
	    tmp->set_line(*obj);

	    if (debug_optimizer)
		  cerr << obj->get_fileline() << ": debug: "
		       << "Replace binary MUX with constant select=" << sel_val
		       << " with a BUFZ to the selected input." << endl;

	    tmp->rise_time(obj->rise_time());
	    tmp->fall_time(obj->fall_time());
	    tmp->decay_time(obj->decay_time());

	    connect(tmp->pin(0), obj->pin_Result());
	    if (sel_val == verinum::V1)
		  connect(tmp->pin(1), obj->pin_Data(1));
	    else
		  connect(tmp->pin(1), obj->pin_Data(0));
	    delete obj;
	    des->add_node(tmp);
	    count += 1;
      }
}
