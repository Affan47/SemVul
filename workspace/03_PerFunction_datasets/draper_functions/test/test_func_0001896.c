shutdown_trigger(int key)
{

  if ((key & ECCPAS0) && trig_state[0])
	return true;

  if ((key & ECCPAS1) && trig_state[1])
	return true;

  if ((key & ECCPAS2) && trig_state[2])
	return true;

  return false;
}
