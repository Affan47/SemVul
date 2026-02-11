cpl_mask_or(cpl_mask        *   in1,
                           const cpl_mask  *   in2)
{
    cpl_ensure_code(in1     != NULL,    CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(in2     != NULL,    CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(in1->nx == in2->nx, CPL_ERROR_INCOMPATIBLE_INPUT);
    cpl_ensure_code(in1->ny == in2->ny, CPL_ERROR_INCOMPATIBLE_INPUT);

    cpl_mask_or_(in1->data, NULL, in2->data, (size_t)(in1->nx * in1->ny));

    return CPL_ERROR_NONE;
}
