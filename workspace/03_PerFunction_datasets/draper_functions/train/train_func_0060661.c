add (char *name)
{
  if (aktpilots >= maxpilots) return;
  aktpilot = aktpilots;
  pilot [aktpilot] = new Pilot (name);
  aktpilots ++;
}
