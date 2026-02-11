image_list_del(struct image_list * list) {

	if ( ! list )
		return;

	image_list_unlink(list);
	image_free(list->image);
	free(list);

}
