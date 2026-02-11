ipcp_input(int linkunit,u_char *p,int len)
{
  int unit = lns[linkunit].ipcp_unit;
  if(unit < 0)
  {
    syslog(LOG_ERR,"ipcp_input: illegal ipcp_unit for linkunit %d",linkunit);
    return;
  }
  fsm_input(&ipcp_fsm[unit], p, len);
}
