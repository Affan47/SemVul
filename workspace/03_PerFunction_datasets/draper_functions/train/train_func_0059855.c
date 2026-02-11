hdrl_image_sub_scalar(hdrl_image * self,
                       double value, double error)
{
    cpl_ensure_code(self, CPL_ERROR_NULL_INPUT);

    return hdrl_elemop_image_sub_scalar(self->image, self->error,
                                          value, error);
}
