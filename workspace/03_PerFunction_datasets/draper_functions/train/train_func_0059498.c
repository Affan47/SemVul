vpip_make_real_var(const char*name, vvp_net_t*net)
{
      struct __vpiRealVar*obj = (struct __vpiRealVar*)
	    malloc(sizeof(struct __vpiRealVar));

      obj->base.vpi_type = &vpip_real_var_rt;
      obj->id.name = name ? vpip_name_string(name) : 0;
      obj->is_netarray = 0;
      obj->net = net;

      obj->within.scope = vpip_peek_current_scope();

      return &obj->base;
}
