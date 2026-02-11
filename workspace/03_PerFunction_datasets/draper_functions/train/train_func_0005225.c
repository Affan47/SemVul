dxf_insert_init
(
        DxfInsert *dxf_insert

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif

        if (dxf_insert == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_insert = dxf_insert_new ();
        }
        if (dxf_insert == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfInsert struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_insert->block_name = strdup ("");
        dxf_insert->id_code = 0;
        dxf_insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_insert->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_insert->x0 = 0.0;
        dxf_insert->y0 = 0.0;
        dxf_insert->z0 = 0.0;
        dxf_insert->elevation = 0.0;
        dxf_insert->thickness = 0.0;
        dxf_insert->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_insert->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_insert->rel_x_scale = 1.0;
        dxf_insert->rel_y_scale = 1.0;
        dxf_insert->rel_z_scale = 1.0;
        dxf_insert->column_spacing = 0.0;
        dxf_insert->row_spacing = 0.0;
        dxf_insert->rot_angle = 0.0;
        dxf_insert->color = DXF_COLOR_BYLAYER;
        dxf_insert->paperspace = DXF_MODELSPACE;
        dxf_insert->attributes_follow = 0;
        dxf_insert->columns = 0;
        dxf_insert->rows = 0;
        dxf_insert->extr_x0 = 0.0;
        dxf_insert->extr_y0 = 0.0;
        dxf_insert->extr_z0 = 0.0;
        dxf_insert->dictionary_owner_soft = strdup ("");
        dxf_insert->dictionary_owner_hard = strdup ("");
        dxf_insert->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_insert);
}
