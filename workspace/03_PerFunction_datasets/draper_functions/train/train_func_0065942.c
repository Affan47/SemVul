announce_deletion(ED4_base *object) {


    ED4_cursor& cursor = get_ed4w()->cursor;
    if (cursor.owner_of_cursor == object) {
        cursor.HideCursor();
        e4_assert(cursor.owner_of_cursor != object);
    }
}
