bm_set_components_argb_32_screen(ubyte *pixel, ubyte *rv, ubyte *gv, ubyte *bv, ubyte *av)
{
	if ( *av == 0 ) {
		*((unsigned int*)pixel) = (unsigned int)Gr_current_green->mask;
		return;
	}

	*((unsigned int*)pixel) = (unsigned int)(( (int)*rv / Gr_current_red->scale ) << Gr_current_red->shift);
	*((unsigned int*)pixel) |= (unsigned int)(( (int)*gv / Gr_current_green->scale ) << Gr_current_green->shift);
	*((unsigned int*)pixel) |= (unsigned int)(( (int)*bv / Gr_current_blue->scale ) << Gr_current_blue->shift);
}
