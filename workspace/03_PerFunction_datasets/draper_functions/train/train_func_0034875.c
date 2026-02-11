irplib_vector_fill_logline_spectrum_fast(cpl_vector * self,
                                         const cpl_polynomial * disp,
                                         irplib_base_spectrum_model * lsslamp)
{

    irplib_line_spectrum_model * arclamp
        = (irplib_line_spectrum_model *)lsslamp;
    cpl_error_code error;

    cpl_ensure_code(arclamp != NULL, CPL_ERROR_NULL_INPUT);

    arclamp->cost++;

    error = irplib_vector_fill_line_spectrum_model(self,
                                                   arclamp->linepix,
                                                   arclamp->erftmp,
                                                   disp,
                                                   arclamp->lines,
                                                   arclamp->wslit,
                                                   arclamp->wfwhm,
                                                   arclamp->xtrunc,
                                                   0, CPL_TRUE, CPL_TRUE,
                                                   &(arclamp->ulines));
    cpl_ensure_code(!error, error);

    arclamp->xcost++;

    return CPL_ERROR_NONE;
}
