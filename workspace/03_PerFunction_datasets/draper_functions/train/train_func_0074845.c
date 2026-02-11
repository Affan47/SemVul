refresh()
{
  if(stimuli) {

    stimulus *sptr = stimuli;

    initial_voltage = get_nodeVoltage();

    switch (nStimuli) {

    case 0:

      break;

    case 1:

      finalVoltage = sptr->get_Vth();
      Zth =  sptr->get_Zth();
      break;

    case 2:


      {
      stimulus *sptr2 = sptr ? sptr->next : 0;
      if(!sptr2)
        break;

      double V1,Z1,C1;
      double V2,Z2,C2;
      sptr->getThevenin(V1,Z1,C1);
      sptr2->getThevenin(V2,Z2,C2);
      finalVoltage = (V1*Z2  + V2*Z1) / (Z1+Z2);
      Zth = Z1*Z2/(Z1+Z2);
      Cth = C1+C2;

      }
      break;

    default:
      {


      double conductance=0.0;
      Cth=0;
      finalVoltage=0.0;


      while(sptr) {

	double V1,Z1,C1;
	sptr->getThevenin(V1,Z1,C1);


        double Cs = 1 / Z1;
        finalVoltage += V1 * Cs;
        conductance += Cs;
        Cth += C1;
        sptr = sptr->next;
      }
      Zth = 1.0/conductance;
      finalVoltage *= Zth;
      }
    }

    current_time_constant = Cth * Zth;
    if(((guint64)(current_time_constant*get_cycles().instruction_cps())
      < min_time_constant)
      ||
      (fabs(finalVoltage - voltage) < minThreshold))
    {
      if (verbose)
        cout << "Stimulus_Node::refresh " << name() << " use DC " <<
		finalVoltage << " as current_time_constant=" <<
          current_time_constant << endl;

      if (future_cycle)
      {
	get_cycles().clear_break(this);
      }

      voltage = finalVoltage;
      future_cycle = 0;

    } else {
	settlingTimeStep = (guint64) (0.11 *
	  get_cycles().instruction_cps() * current_time_constant);
	voltage = initial_voltage;

        if (verbose)
	  cout << "Stimulus_Node::refresh " << name() << " settlingTimeStep="
	    << settlingTimeStep << " voltage=" << voltage << " Finalvoltage="
	    << finalVoltage << endl;


      if (future_cycle)
      {
	callback();
      }
      else
      {
	cap_start_cycle = get_cycles().get();
        future_cycle = cap_start_cycle + settlingTimeStep;
        get_cycles().set_break(future_cycle,this);
      }
    }

  }


}
