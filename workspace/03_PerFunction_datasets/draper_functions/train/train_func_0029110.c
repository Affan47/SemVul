irplib_slitpos_find_edges_one_line(const cpl_image * self,
                                                         int          line_pos,
                                                         int        * left_pos,
                                                         int        * right_pos)
{
    const int     size_x = cpl_image_get_size_x(self);
    const float * pself;
    double        threshold;
    int           i;

    cpl_ensure_code(self != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(cpl_image_get_type(self) == CPL_TYPE_FLOAT,
                    CPL_ERROR_INVALID_TYPE);

    pself = cpl_image_get_data_float_const(self);


    threshold = cpl_image_get_mean_window(self, 1, line_pos+1, size_x,
                                          line_pos+1);


    i = 0;
    while (i < size_x && pself[line_pos*size_x+i] < threshold) i++;
    *left_pos = i;


    i = size_x - 1;
    while (i >= 0 && pself[line_pos*size_x+i] < threshold) i--;
    *right_pos = i;

    return CPL_ERROR_NONE;
}
