aiinit ()
{
  int i;
  acttype = 0;
  dualshot = false;
  intelligence = 100;
  aggressivity = 100;
  precision = 100;
  shield = 0.01F;
  ai = true;
  active = true;
  draw = true;
  target = NULL;
  dtheta = 0;
  dgamma = 0;
  id = MISSILE1;
  impact = 30;
  manoevertheta = 0;
  manoeverheight = 0;
  manoeverthrust = 0;
  idle = 0;
  smokettl = 0;
  firecannonttl = 0;
  firemissilettl = 0;
  fireflarettl = 0;
  firechaffttl = 0;
  flares = 0;
  aw = 0;
  source = NULL;
  points = 0;
  easymodel = 1;
  elevatoreffect = 0;
  ruddereffect = 0;
  gamma = 180;
  recgamma = 180;
  dgamma = 0;
  theta = 0;
  maxgamma = 70;
  maxtheta = 90;
  missiletype = 0;
  autofire = false;
  ttl = -1;
  ttf = 30 * timestep;
  score = -1;
  for (i = 0; i < missiletypes; i ++)
    missiles [i] = 0;
  for (i = 0; i < missileracks; i ++)
  {
    missilerack [i] = -1;
    missilerackn [i] = 0;
  }
  bomber = 0;
  timer = 0;
  ammo = -1;
  manoeverstate = 0;
}
