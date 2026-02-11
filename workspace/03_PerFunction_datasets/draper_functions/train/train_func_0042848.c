cdj970_print_non_blank_lines(	 gx_device_printer 			*pdev,
                                                                                                                                                                                 struct ptr_arrays 			*data_ptrs,
                                                                                                                                                                                 struct misc_struct 		*misc_vars,
                                                                                                                                                                                 struct error_val_field *error_values,
                                                                                                                                                                                 const Gamma 						*gamma,
                                                                                                                                                                                 FILE 									*prn_stream)
{
        static const char *const plane_code[2] = {"vvvv", "wvvv"};

        int 	i;
        byte 	*kP = data_ptrs->plane_data[misc_vars->scan + 2][3];
        byte 	*dp = data_ptrs->data[misc_vars->scan + 2];
        int 	*ep = data_ptrs->errors[misc_vars->scan];


        misc_vars->is_color_data =
                                                                do_gcr(misc_vars->databuff_size, data_ptrs->data[misc_vars->scan],
                                                                gamma->k, gamma->c, gamma->m, gamma->y, gamma->correct);


        FSDlinebw(misc_vars->scan, misc_vars->plane_size,
                                                        error_values, kP, misc_vars->num_comps, ep, dp);

        print_c2plane(prn_stream, 'v', misc_vars->plane_size,
                                                                                                data_ptrs->plane_data[misc_vars->scan][3],
                                                                                                data_ptrs->plane_data[1 - misc_vars->scan][3],
                                                                                                data_ptrs->out_data);


        if (!cdj970->yscal || misc_vars->is_two_pass) {
                int plane_size_c = (*rescale_color_plane[cdj970->xscal][cdj970->yscal])
                                                                                                        (misc_vars->databuff_size,
                                                                                                        data_ptrs->data[misc_vars->scan],
                                                                                                        data_ptrs->data[1 - misc_vars->scan],
                                                                                                        data_ptrs->data_c[misc_vars->cscan]) / misc_vars->storage_bpp;


                do_floyd_steinberg(misc_vars->scan, misc_vars->cscan,
                                                                                                        misc_vars->plane_size, plane_size_c,
                                                                                                        misc_vars->num_comps, data_ptrs, pdev, error_values);


                for (i = misc_vars->num_comps - 2; i >= 0; i--) {


                        if (cdj970->intensities > 2) {

                                print_c2plane(prn_stream, plane_code[0][i], plane_size_c,
                                                                                                        data_ptrs->plane_data_c[misc_vars->cscan][i + 4],
                                                                                                        data_ptrs->plane_data_c[1 - misc_vars->cscan][i + 4],
                                                                                                        data_ptrs->out_data);

                        }
                        print_c2plane(prn_stream, plane_code[1][i],
                                                                                                        plane_size_c,
                                                                                                        data_ptrs->plane_data_c[misc_vars->cscan][i],
                                                                                                        data_ptrs->plane_data_c[1 - misc_vars->cscan][i],
                                                                                                        data_ptrs->out_data);

                }

                misc_vars->cscan = 1 - misc_vars->cscan;

        }

        return;
}
