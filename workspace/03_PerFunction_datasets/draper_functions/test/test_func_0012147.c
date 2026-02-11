measure_ports(GanvModule* module)
{
	GanvModuleImpl* impl = module->impl;

	impl->widest_input  = 0.0;
	impl->widest_output = 0.0;
	FOREACH_PORT_CONST(impl->ports, pi) {
		const GanvPort* const p = (*pi);
		const double          w = ganv_port_get_natural_width(p);
		if (p->impl->is_input) {
			if (w > impl->widest_input) {
				impl->widest_input = w;
			}
		} else {
			if (w > impl->widest_output) {
				impl->widest_output = w;
			}
		}
	}
}
