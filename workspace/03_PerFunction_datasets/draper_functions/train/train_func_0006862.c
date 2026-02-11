get_Vth()
{
  guint64 current_time = get_cycles().get();


  guint64 t = (current_time+phase) % period;

  double ret_val;

  if( t <= duty)
    ret_val = b1 + m1 * t;
  else
    ret_val = b2 + m2 * t;


  return ret_val;

}
