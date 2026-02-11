dxf_3dsolid_free
(
        Dxf3dsolid *dxf_3dsolid


)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;


        if (dxf_3dsolid->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next Dxf3dsolid was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_3dsolid->linetype);
        free (dxf_3dsolid->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_3dsolid->proprietary_data[i]);
                free (dxf_3dsolid->additional_proprietary_data[i]);
        }
        free (dxf_3dsolid);
        dxf_3dsolid = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
