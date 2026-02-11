dxf_image_init
(
        DxfImage *dxf_image

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;


        if (dxf_image == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_image = dxf_image_new ();
        }
        if (dxf_image == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfImage struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_image->id_code = 0;
        dxf_image->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_image->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_image->thickness = 0.0;
        dxf_image->color = DXF_COLOR_BYLAYER;
        dxf_image->paperspace = DXF_MODELSPACE;
        dxf_image->x0 = 0.0;
        dxf_image->y0 = 0.0;
        dxf_image->z0 = 0.0;
        dxf_image->x1 = 0.0;
        dxf_image->y1 = 0.0;
        dxf_image->z1 = 0.0;
        dxf_image->x2 = 0.0;
        dxf_image->y2 = 0.0;
        dxf_image->z2 = 0.0;
        dxf_image->x3 = 0.0;
        dxf_image->y3 = 0.0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_image->x4[i] = 0.0;
                dxf_image->y4[i] = 0.0;
        }
        dxf_image->image_display_properties = 0;
        dxf_image->clipping_boundary_type = 0;
        dxf_image->class_version = 0;
        dxf_image->number_of_clip_boundary_vertices = 0;
        dxf_image->clipping_state = 0;
        dxf_image->brightness = 50;
        dxf_image->contrast = 50;
        dxf_image->fade = 50;
        dxf_image->imagedef_object = strdup ("");
        dxf_image->imagedef_reactor_object = strdup ("");
        dxf_image->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_image);
}
