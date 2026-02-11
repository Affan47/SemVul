dxf_hatch_boundary_path_edge_spline_append_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,

        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp


)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_hatch_boundary_path_edge_spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_hatch_boundary_path_edge_spline_cp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline_cp.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (dxf_hatch_boundary_path_edge_spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                dxf_hatch_boundary_path_edge_spline = realloc (dxf_hatch_boundary_path_edge_spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (dxf_hatch_boundary_path_edge_spline->control_points == NULL)
        {


                dxf_hatch_boundary_path_edge_spline->control_points = dxf_hatch_boundary_path_edge_spline_cp;
        }
        else
        {


                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) dxf_hatch_boundary_path_edge_spline->control_points;
                for (;;)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        if (iter->next == NULL)
                        {
                                break;
                        }
                }


                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = dxf_hatch_boundary_path_edge_spline_cp->id_code;
                new->x0 = dxf_hatch_boundary_path_edge_spline_cp->x0;
                new->y0 = dxf_hatch_boundary_path_edge_spline_cp->y0;
                new->weight = dxf_hatch_boundary_path_edge_spline_cp->weight;
                new->next = NULL;

                iter->next = new;
                dxf_hatch_boundary_path_edge_spline->number_of_control_points++;

                dxf_hatch_boundary_path_edge_spline_control_point_free (dxf_hatch_boundary_path_edge_spline_cp);
                dxf_hatch_boundary_path_edge_spline_cp = NULL;
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
