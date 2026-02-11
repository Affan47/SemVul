GMT_vstereo (double lon0, double lat0, double horizon)
{


	double clat;

	if (project_info.GMT_convert_latitudes) {
		GMT_scale_eqrad ();
		clat = GMT_latg_to_latc (lat0);
	}
	else
		clat = lat0;

	project_info.central_meridian = lon0;
	project_info.pole = lat0;
	sincosd (clat, &(project_info.sinp), &(project_info.cosp));
	project_info.north_pole = (lat0 > 0.0);
	project_info.s_c = 2.0 * project_info.EQ_RAD * gmtdefs.map_scale_factor;
	project_info.s_ic = 1.0 / project_info.s_c;
	project_info.f_horizon = horizon;
	project_info.rho_max = tand (0.5 * horizon) * project_info.s_c;
}
