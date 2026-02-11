gold_at(short row, short col)
{
    if (dungeon[row][col] & OBJECT) {
	object *obj;

	if ((obj = object_at(&level_objects, row, col)) &&
	    (obj->what_is == GOLD)) {
	    return 1;
	}
    }
    return 0;
}
