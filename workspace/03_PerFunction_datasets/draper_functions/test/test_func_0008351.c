gui_save_object(struct gui_object *cur)
{
	char tmp[256];
	DBT key, data;
	int res;
	if (db && cur) {
		if (strlen(cur->ident)) {
			snprintf(tmp, sizeof(tmp), "%d:%d", cur->widget->allocation.x, cur->widget->allocation.y);
			memset(&key, 0, sizeof(key));
			memset(&data, 0, sizeof(data));
			key.data = cur->ident;
			key.size = strlen(cur->ident) + 1;
			data.data = tmp;
			data.size = strlen(tmp) + 1;
#ifdef __FreeBSD__
			if ((res = db->put(db, &key, &data, 0)))
#else
			if ((res = db->put(db, NULL, &key, &data, 0)))
#endif
				fprintf(stderr, "Unable to save '%s' location\n", cur->ident);

		}
	}
	return 0;
}
