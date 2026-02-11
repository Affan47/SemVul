idntfy(void)
{
    short ch;
    object *obj;
    struct id *id_table;
    char desc[ROGUE_COLUMNS];
AGAIN:
    ch = pack_letter(mesg[260], ALL_OBJECTS);
    if (ch == CANCEL) {
	return;
    }
    if (!(obj = get_letter_object(ch))) {
	message(mesg[261], 0);
	message("", 0);
	check_message();
	goto AGAIN;
    }
    obj->identified = 1;
    if (obj->what_is & (SCROL | POTION | WEAPON | ARMOR | WAND | RING)) {
	id_table = get_id_table(obj);
	id_table[obj->which_kind].id_status = IDENTIFIED;
    }
    get_desc(obj, desc, 1);
    message(desc, 0);
}
