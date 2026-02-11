el_bind_key_in_map(int key, el_keymap_func_t function, el_keymap_t map[], size_t mapsz)
{
    size_t creat, pos = find_key_in_map(key, map, mapsz);

    if (pos == mapsz) {
	errno = ENOMEM;
	return CSeof;
    }


    creat = map[pos].Function == NULL;


    map[pos].Key	  = key;
    map[pos].Function	  = function;


    if (creat) {
	map[pos + 1].Key      = 0;
	map[pos + 1].Function = NULL;
    }

    return CSdone;
}
