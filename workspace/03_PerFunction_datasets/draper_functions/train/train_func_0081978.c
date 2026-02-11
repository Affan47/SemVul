dxf_hatch_boundary_path_edge_line_init
(
        DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        dxf_hatch_boundary_path_edge_line = dxf_hatch_boundary_path_edge_line_new ();
        if (dxf_hatch_boundary_path_edge_line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeLine struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_hatch_boundary_path_edge_line->id_code = 0;
        dxf_hatch_boundary_path_edge_line->x0 = 0.0;
        dxf_hatch_boundary_path_edge_line->y0 = 0.0;
        dxf_hatch_boundary_path_edge_line->x1 = 0.0;
        dxf_hatch_boundary_path_edge_line->y1 = 0.0;
        dxf_hatch_boundary_path_edge_line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_hatch_boundary_path_edge_line);
}
