adjust_subregion (GtkSourceSearchContext *search,
		  GtkTextIter            *start,
		  GtkTextIter            *end)
{
	DEBUG ({
		g_print ("adjust_subregion(), before adjusting: [%u (%u), %u (%u)]\n",
			 gtk_text_iter_get_line (start), gtk_text_iter_get_offset (start),
			 gtk_text_iter_get_line (end), gtk_text_iter_get_offset (end));
	});

	gtk_text_iter_backward_lines (start, MAX (0, search->priv->text_nb_lines - 1));
	gtk_text_iter_forward_lines (end, MAX (0, search->priv->text_nb_lines - 1));

	if (!gtk_text_iter_starts_line (start))
	{
		gtk_text_iter_set_line_offset (start, 0);
	}

	if (!gtk_text_iter_ends_line (end))
	{
		gtk_text_iter_forward_to_line_end (end);
	}


	if (gtk_text_iter_has_tag (start, search->priv->found_tag))
	{
		if (is_text_region_empty (search->priv->scan_region))
		{

			gtk_text_iter_forward_to_tag_toggle (start, search->priv->found_tag);
		}
		else
		{
			GtkTextIter tag_start = *start;
			GtkTextIter tag_end = *start;
			GtkTextRegion *region;

			if (!gtk_text_iter_begins_tag (&tag_start, search->priv->found_tag))
			{
				gtk_text_iter_backward_to_tag_toggle (&tag_start, search->priv->found_tag);
			}

			gtk_text_iter_forward_to_tag_toggle (&tag_end, search->priv->found_tag);

			region = gtk_text_region_intersect (search->priv->scan_region,
							    &tag_start,
							    &tag_end);

			if (is_text_region_empty (region))
			{


				*start = tag_end;
			}
			else
			{


				*start = tag_start;
			}

			if (region != NULL)
			{
				gtk_text_region_destroy (region);
			}
		}
	}


	if (gtk_text_iter_has_tag (end, search->priv->found_tag))
	{
		if (is_text_region_empty (search->priv->scan_region))
		{


			if (!gtk_text_iter_begins_tag (end, search->priv->found_tag))
			{
				gtk_text_iter_backward_to_tag_toggle (end, search->priv->found_tag);
			}
		}
		else
		{
			GtkTextIter tag_start = *end;
			GtkTextIter tag_end = *end;
			GtkTextRegion *region;

			if (!gtk_text_iter_begins_tag (&tag_start, search->priv->found_tag))
			{
				gtk_text_iter_backward_to_tag_toggle (&tag_start, search->priv->found_tag);
			}

			gtk_text_iter_forward_to_tag_toggle (&tag_end, search->priv->found_tag);

			region = gtk_text_region_intersect (search->priv->scan_region,
							    &tag_start,
							    &tag_end);

			if (is_text_region_empty (region))
			{


				*end = tag_start;
			}
			else
			{


				*end = tag_end;
			}

			if (region != NULL)
			{
				gtk_text_region_destroy (region);
			}
		}
	}

	DEBUG ({
		g_print ("adjust_subregion(), after adjusting: [%u (%u), %u (%u)]\n",
			 gtk_text_iter_get_line (start), gtk_text_iter_get_offset (start),
			 gtk_text_iter_get_line (end), gtk_text_iter_get_offset (end));
	});
}
