add_album_button_clicked(void *data, Evas_Object *obj, void *event_info)
{

	Evas_Object *li = data;
	const Eina_List *item;

	while((item = elm_genlist_selected_items_get(li))) {
		char *album = (char *)elm_object_item_data_get(item->data);
		add_songs_from_album(album, c_play_list);
		if (album) free(album);
		elm_object_item_del(item->data);
	}
}
