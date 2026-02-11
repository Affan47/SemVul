swf_svg_print_matrix(SWFReader *read, GF_Matrix2D *mat)
{
    if (!gf_mx2d_is_identity(*mat))
    {
        GF_Point2D  scale;
        GF_Point2D  translate;
        Fixed       rotate;
        if( gf_mx2d_decompose(mat, &scale, &rotate, &translate))
        {
            fprintf(read->svg_output, "transform=\"");
            if (translate.x != 0 || translate.y != 0)
            {
                fprintf(read->svg_output, "translate(%f, %f) ", translate.x, translate.y);
            }
            if (rotate != 0)
            {
                fprintf(read->svg_output, "rotate(%f) ", rotate);
            }
            if (scale.x != FIX_ONE || scale.y != FIX_ONE)
            {
                fprintf(read->svg_output, "scale(%f, %f) ", scale.x, scale.y);
            }
            fprintf(read->svg_output, "\" ");
        }
        else
        {
            fprintf(read->svg_output, "transform=\"matrix(%f,%f,%f,%f,%f,%f)\" ", mat->m[0], mat->m[3], mat->m[1], mat->m[4], mat->m[2], mat->m[5]);
        }
    }
}
