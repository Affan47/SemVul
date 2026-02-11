dxf_style_init
(
        DxfStyle *dxf_style

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif

        if (dxf_style == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_style = dxf_style_new ();
        }
        if (dxf_style == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_style->id_code = 0;
        dxf_style->style_name = strdup ("");
        dxf_style->primary_font_filename = strdup ("");
        dxf_style->big_font_filename = strdup ("");
        dxf_style->height = 0.0;
        dxf_style->width = 0.0;
        dxf_style->last_height = 0.0;
        dxf_style->oblique_angle = 0.0;
        dxf_style->flag = 0;
        dxf_style->text_generation_flag = 0;
        dxf_style->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_style);
}
