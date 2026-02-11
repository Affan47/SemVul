gl_label_select_region (glLabel       *label,
                        glLabelRegion *region)
{
	GList         *p;
	glLabelObject *object;
        gdouble        r_x1, r_y1;
        gdouble        r_x2, r_y2;
        glLabelRegion  obj_extent;

	gl_debug (DEBUG_LABEL, "START");

	g_return_if_fail (label && GL_IS_LABEL (label));

        r_x1 = MIN (region->x1, region->x2);
        r_y1 = MIN (region->y1, region->y2);
        r_x2 = MAX (region->x1, region->x2);
        r_y2 = MAX (region->y1, region->y2);

	for (p = label->priv->object_list; p != NULL; p = p->next)
        {
		object = GL_LABEL_OBJECT(p->data);

                gl_label_object_get_extent (object, &obj_extent);
                if ((obj_extent.x1 >= r_x1) &&
                    (obj_extent.x2 <= r_x2) &&
                    (obj_extent.y1 >= r_y1) &&
                    (obj_extent.y2 <= r_y2))
                {
                        gl_label_object_select (object);
                }
	}

        label->priv->cp_cleared_flag = TRUE;
	g_signal_emit (G_OBJECT(label), signals[SELECTION_CHANGED], 0);

	gl_debug (DEBUG_LABEL, "END");
}
