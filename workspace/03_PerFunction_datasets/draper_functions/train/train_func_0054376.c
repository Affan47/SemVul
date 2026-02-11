_create_resv_info_list(reserve_info_msg_t *resv_info_ptr)
{
	static List info_list = NULL;
	List last_list = NULL;
	ListIterator last_list_itr = NULL;
	int i = 0;
	static reserve_info_msg_t *last_resv_info_ptr = NULL;
	sview_resv_info_t *sview_resv_info_ptr = NULL;
	reserve_info_t *resv_ptr = NULL;

	if (info_list && (resv_info_ptr == last_resv_info_ptr))
		goto update_color;

	last_resv_info_ptr = resv_info_ptr;

	if (info_list)
		last_list = info_list;

	info_list = list_create(_resv_info_list_del);
	if (!info_list) {
		g_print("malloc error\n");
		return NULL;
	}

	if (last_list)
		last_list_itr = list_iterator_create(last_list);
	for(i=0; i<resv_info_ptr->record_count; i++) {
		resv_ptr = &(resv_info_ptr->reservation_array[i]);

		sview_resv_info_ptr = NULL;

		if (last_list_itr) {
			while ((sview_resv_info_ptr =
				list_next(last_list_itr))) {
				if (!strcmp(sview_resv_info_ptr->resv_name,
					    resv_ptr->name)) {
					list_remove(last_list_itr);
					_resv_info_free(sview_resv_info_ptr);
					break;
				}
			}
			list_iterator_reset(last_list_itr);
		}
		if (!sview_resv_info_ptr)
			sview_resv_info_ptr =
				xmalloc(sizeof(sview_resv_info_t));
		sview_resv_info_ptr->pos = i;
		sview_resv_info_ptr->resv_ptr = resv_ptr;
		sview_resv_info_ptr->color_inx = i % sview_colors_cnt;
		list_append(info_list, sview_resv_info_ptr);
	}

	list_sort(info_list,
		  (ListCmpF)_sview_resv_sort_aval_dec);

	if (last_list) {
		list_iterator_destroy(last_list_itr);
		list_destroy(last_list);
	}

update_color:
	return info_list;
}
