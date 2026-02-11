get_Vth()
{
  guint64 current_time = get_cycles().get();

  if(verbose & 1)
    cout << "Getting new state of the square wave.\n";

  if( ((current_time+phase) % period) <= duty)
    return  Vth;
  else
    return  0.0;
}
