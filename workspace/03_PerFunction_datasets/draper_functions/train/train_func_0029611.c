light_set_all_relevent()
{
	int idx;

	gr_reset_lighting();

	for (idx = 0; idx < (int)Static_light.size(); idx++)
		gr_set_light( Static_light[idx] );


	int n = Num_light_levels-1;

	for (idx = 0; idx < Num_relevent_lights[n]; idx++ )
		gr_set_light( Relevent_lights[idx][n] );
}
