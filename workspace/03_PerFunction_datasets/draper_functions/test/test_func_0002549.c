cpl_mask_set(cpl_mask * self,
                            cpl_size   xpos,
                            cpl_size   ypos,
                            cpl_binary value)
{

    cpl_ensure_code(self != NULL,     CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(xpos > 0,         CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(ypos > 0,         CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(xpos <= self->nx, CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(ypos <= self->ny, CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(value == CPL_BINARY_0 || value == CPL_BINARY_1,
                    CPL_ERROR_ILLEGAL_INPUT);

    self->data[(xpos-1) + (ypos-1) * self->nx] = value;

    return CPL_ERROR_NONE;
}
