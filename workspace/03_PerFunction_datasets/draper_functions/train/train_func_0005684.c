set_value(int x, int y){
  ant_val=act_val;

  if(x_direction) act_val=x;
  else act_val=(-1)*y;
  if (first_time){
    if(act_val>0) ant_val=act_val-1;
    else if(act_val<0) ant_val=act_val+1;
    first_time=false;
  }

  switch(filter_type){
    case GAIN_TYPE:
       *mouse_value =  *mouse_value + (float)(act_val-ant_val)/ACCELERATION;
      if (*mouse_value > GAIN_MAX) *mouse_value = GAIN_MAX;
      else if (*mouse_value < GAIN_MIN) *mouse_value = GAIN_MIN;
    break;

    case FREQ_TYPE:
      acumula=acumula+ (act_val-ant_val);
      if (acumula >= 6) ptr++;
      else if (acumula <= -6) ptr--;
      acumula = acumula %6;
      if (ptr >= NUM_POINTS) ptr = NUM_POINTS -1;
      else if (ptr < 0) ptr = 0;
      *mouse_value = f_ptr[ptr];
    break;

    case Q_TYPE:
      *mouse_value =  *mouse_value + (float)(act_val-ant_val)/ACCELERATION;
      if (*mouse_value > PEAK_Q_MAX) *mouse_value = PEAK_Q_MAX;
      else if (*mouse_value < PEAK_Q_MIN) *mouse_value = PEAK_Q_MIN;
    break;
   }


  eqbutton_ref_ptr->set_value(*mouse_value);
  eqbutton_ref_ptr->set_spin_number();


}
