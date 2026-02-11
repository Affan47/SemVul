vml_polyline(GVJ_t * job, pointf * A, int n)
{
    int i;

    gvputs(job, " <v:shape style=\"position:absolute; ");
    gvprintf(job, " width: %d; height: %d\" filled=\"false\">", graphWidth, graphHeight);
    gvputs(job, "<v:path v=\"");
    for (i = 0; i < n; i++)
    {
        if (i==0) gvputs(job, " m ");
	gvprintf(job, "%.0f,%.0f ", A[i].x, graphHeight-A[i].y);
        if (i==0) gvputs(job, " l ");
        if (i==n-1) gvputs(job, " e ");
    }
    gvputs(job, "\"/>");
    vml_grstroke(job, 0);
    gvputs(job, "</v:shape>\n");
}
