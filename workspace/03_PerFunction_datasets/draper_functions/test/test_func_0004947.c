dxf_hatch_boundary_path_write
(
        DxfFile *fp,

        DxfHatchBoundaryPath *dxf_hatch_boundary_path

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolyline *iter;


        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_hatch_boundary_path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }

        for (;;)
        {
                if (dxf_hatch_boundary_path->next == NULL)
                {
                        fprintf (stderr,
                          (_("Information from %s () last boundary path encountered.\n")),
                          __FUNCTION__);
                        break;
                }
                else
                {

                        if (dxf_hatch_boundary_path->edges != NULL)
                        {

                        }
                        else if (dxf_hatch_boundary_path->polylines != NULL)
                        {
                                iter = dxf_hatch_boundary_path_polyline_new ();
                                iter = (DxfHatchBoundaryPathPolyline *) dxf_hatch_boundary_path->polylines;
                                for (;;)
                                {
                                        dxf_hatch_boundary_path_polyline_write
                                        (
                                                fp,
                                                iter
                                        );
                                        iter = (DxfHatchBoundaryPathPolyline *) iter->next;
                                        if (iter == NULL)
                                        {
                                                break;
                                        }
                                }
                        }
                        else
                        {
                                fprintf (stderr,
                                  (_("Error in %s () unknown boundary path type encountered.\n")),
                                  __FUNCTION__);
                                return (EXIT_FAILURE);
                        }
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
