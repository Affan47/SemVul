hawki_distortion_create_maps_detector
(const hawki_distortion * distortion,
 cpl_image              * dist_x,
 cpl_image              * dist_y)
{
    double              *   pdx;
    double              *   pdy;
    int                     nx, ny;
    int                     pos;
    int                     i, j;


    if (distortion == NULL) return -1 ;
    if (dist_x == NULL) return -1 ;
    if (dist_y == NULL) return -1 ;


    nx = cpl_image_get_size_x(dist_x) ;
    ny = cpl_image_get_size_y(dist_x) ;
    if (cpl_image_get_size_x(dist_y) != nx) return -1 ;
    if (cpl_image_get_size_y(dist_y) != ny) return -1 ;


    pdx = cpl_image_get_data_double(dist_x) ;
    pdy = cpl_image_get_data_double(dist_y) ;


    for (j=0 ; j<ny ; j++) {
        for (i=0 ; i<nx ; i++) {
            double x_dist;
            double y_dist;

            pos = i+j*nx ;

            hawki_distortion_interpolate_distortion
                (distortion, (double)i, (double)j, &x_dist, &y_dist);

            pdx[pos] = x_dist;
            pdy[pos] = y_dist;
        }
    }

    return 0 ;
}
