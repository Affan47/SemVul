fi_gui_set_sources(struct fileinfo_data *file)
{
	g_return_if_fail(file);

	if (file->sources) {
		hash_list_iter_t *iter;

		fi_gui_source_massive_update(TRUE);

		iter = hash_list_iterator(file->sources);
		while (hash_list_iter_has_next(iter)) {
			fi_gui_source_show(hash_list_iter_next(iter));
		}
		hash_list_iter_release(&iter);

		fi_gui_source_massive_update(FALSE);
	}
	downloads_gui_update_popup_sources();
}
