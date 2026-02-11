lattr_check(struct lattr_db *db, long amnt)
{
	if (amnt > db->ehole - db->hole) {


		amnt = amnt - (db->ehole - db->hole) + 16;
		db->buffer = (HIGHLIGHT_STATE *)realloc(db->buffer, (db->end + amnt) * sizeof(HIGHLIGHT_STATE));
		mmove(db->buffer + db->ehole + amnt, db->buffer + db->ehole, (db->end - db->ehole) * sizeof(HIGHLIGHT_STATE));
		db->ehole += amnt;
		db->end += amnt;
	}
}
