dxf_shape_free
(
        DxfShape *dxf_shape


)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_shape->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfShape was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_shape->shape_name);
        free (dxf_shape->linetype);
        free (dxf_shape->layer);
        free (dxf_shape->dictionary_owner_soft);
        free (dxf_shape->dictionary_owner_hard);
        free (dxf_shape);
        dxf_shape = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
