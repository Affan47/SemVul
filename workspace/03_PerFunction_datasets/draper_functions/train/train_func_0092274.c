set_slave()
{
  mark_always_q_for_eval();
  if (subckt()) {
    subckt()->set_slave();
  }else{
  }
}
