take_down_alignment (gpointer object, gpointer user_data)
{
	gint i;
	T_Alignment *alignment;

	alignment = (T_Alignment *) object;

	if (alignment->direction == 1)
		for (i = alignment->x; i < alignment->x + alignment->length; i++)
			sge_object_zoomout (g_gem_objects[i][alignment->y]);
	else
		for (i = alignment->y; i < alignment->y + alignment->length; i++)
			sge_object_zoomout (g_gem_objects[alignment->x][i]);
}
