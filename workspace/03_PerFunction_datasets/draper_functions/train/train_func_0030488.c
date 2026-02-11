compute_scale_fit_to (Sheet const *sheet,
		      int start, int end, double usable,
		      ColRowInfo const *(get_info)(Sheet const *sheet, int const p),
		      double (get_distance_pts) (Sheet const *sheet, int from, int to),
		      gint pages, double max_percent, double header,
		      gboolean repeat, gint repeat_start, gint repeat_end, GnmPageBreaks *pb)
{
	double max_p, min_p;
	gint   max_pages;
	double extent;

	extent = get_distance_pts (sheet, start, end + 1);


	if (repeat && (repeat_start < start))
		extent += get_distance_pts (sheet, repeat_start,
					    (repeat_end < start) ? (repeat_end + 1) : start);


	if (pages <= 0)
		return max_percent;


	if (pages == 1) {
		max_p = usable/(header + extent + 2.);
		return ((max_p > max_percent) ? max_percent : max_p);
	}


	max_p = (pages * usable)/(extent + pages * header);
	if (max_p > max_percent)
		max_p = max_percent;

	max_pages = paginate (NULL, sheet, start, end, usable/max_p - header,
			      repeat, repeat_start, repeat_end,
			      get_distance_pts, get_info, pb, FALSE);

	if (max_pages == pages)
		return max_p;


	min_p = usable/(extent + header);
	if (min_p > max_percent)
		min_p = max_percent;

	paginate (NULL, sheet, start, end, usable/min_p - header,
		  repeat, repeat_start, repeat_end,
		  get_distance_pts, get_info, pb, FALSE);


	while (max_p - min_p > 0.001) {
		double cur_p = (max_p + min_p) / 2.;
		int cur_pages = paginate (NULL, sheet, start, end, usable/cur_p - header,
					  repeat, repeat_start, repeat_end,
					  get_distance_pts, get_info, pb, FALSE);

		if (cur_pages > pages)
			max_p = cur_p;
		else
			min_p = cur_p;
	}

	return min_p;
}
