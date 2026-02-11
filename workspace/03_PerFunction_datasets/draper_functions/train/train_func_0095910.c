color_list_remove_all(struct ColorList* color_list){
	ColorList::iter i;
	if (color_list->on_clear){
		color_list->on_clear(color_list);
		for (i=color_list->colors.begin(); i!=color_list->colors.end(); ++i){
			color_object_release(*i);
		}
	}else{
		for (i=color_list->colors.begin(); i!=color_list->colors.end(); ++i){
			if (color_list->on_delete) color_list->on_delete(color_list, *i);
			color_object_release(*i);
		}
	}

	color_list->colors.clear();
	return 0;
}
