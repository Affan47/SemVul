select_b(const P7_OPROFILE *om, const P7_OMX *ox, int i)
{
  float path[2];

  path[0] = ( (om->xf[p7O_N][p7O_MOVE] == 0.0) ? -eslINFINITY : ox->xmx[i*p7X_NXCELLS+p7X_N]);
  path[1] = ( (om->xf[p7O_J][p7O_MOVE] == 0.0) ? -eslINFINITY : ox->xmx[i*p7X_NXCELLS+p7X_J]);
  return  ((path[0] > path[1]) ? p7T_N : p7T_J);
}
