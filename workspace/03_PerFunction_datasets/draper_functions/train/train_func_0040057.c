gnm_so_polygon_finalize (GObject *object)
{
	GnmSOPolygon *sop = GNM_SO_POLYGON (object);

	g_object_unref (sop->style);
	sop->style = NULL;
	if (sop->points != NULL) {
		g_array_free (sop->points, TRUE);
		sop->points = NULL;
	}
	G_OBJECT_CLASS (gnm_so_polygon_parent_class)->finalize (object);
}
