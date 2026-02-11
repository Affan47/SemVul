pdf_calculate_text_size(gs_imager_state *pis, pdf_font_resource_t *pdfont,
                              const gs_matrix *pfmat, gs_matrix *smat, gs_matrix *tmat,
                              gs_font *font, gx_device_pdf *pdev)
{
    gs_matrix orig_matrix;
    double
        sx = pdev->HWResolution[0] / 72.0,
        sy = pdev->HWResolution[1] / 72.0;
    float size;


    {
        gs_font_base *cfont = pdf_font_resource_font(pdfont, false);

        if (pdfont->FontType == ft_user_defined ||
            pdfont->FontType == ft_PCL_user_defined ||
            pdfont->FontType == ft_MicroType ||
            pdfont->FontType == ft_GL2_stick_user_defined ||
            pdfont->FontType == ft_GL2_531)
            orig_matrix = pdfont->u.simple.s.type3.FontMatrix;
        else if (cfont != 0) {


            orig_matrix = cfont->FontMatrix;
        } else {


            pdf_font_orig_matrix(font, &orig_matrix);
        }
    }


    gs_matrix_invert(&orig_matrix, smat);
    gs_matrix_multiply(smat, pfmat, smat);
    *tmat = ctm_only(pis);
    tmat->tx = tmat->ty = 0;
    gs_matrix_multiply(smat, tmat, tmat);


    size = hypot(tmat->yx, tmat->yy) / sy;
    if (size < 0.01)
        size = hypot(tmat->xx, tmat->xy) / sx;
    if (size < 0.01)
        size = 1;

    return(size);
}
