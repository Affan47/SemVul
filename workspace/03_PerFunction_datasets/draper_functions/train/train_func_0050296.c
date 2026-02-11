cpl_image_collapse_create(const cpl_image * self,
                                      int               direction)
{
    cpl_image * other
        = cpl_image_collapse_window_create(self, 1, 1,
                                           cpl_image_get_size_x(self),
                                           cpl_image_get_size_y(self),
                                           direction);


    cpl_ensure(other != NULL, cpl_error_get_code(), NULL);

    return other;
}
