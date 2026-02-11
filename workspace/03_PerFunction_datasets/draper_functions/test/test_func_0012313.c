_e_exehist_load(void)
{
   if (!_e_exehist)
     _e_exehist = e_config_domain_load("exehist", _e_exehist_config_edd);
   if (!_e_exehist)
     _e_exehist = E_NEW(E_Exehist, 1);
}
