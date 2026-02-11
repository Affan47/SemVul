write_point(struct Map_info *Out, double x, double y, double z,
		 int line_cat, double along, int table)
{
    char buf[2000];

    G_debug(3, "write_point()");

    Vect_reset_line(PPoints);
    Vect_reset_cats(PCats);


    Vect_append_point(PPoints, x, y, z);
    Vect_cat_set(PCats, 1, line_cat);
    Vect_cat_set(PCats, 2, point_cat);
    Vect_write_line(Out, GV_POINT, PPoints, PCats);


    if (!table) {
	db_zero_string(&stmt);
	sprintf(buf, "insert into %s values ( %d, %d, %.15g )", Fi->table,
		point_cat, line_cat, along);
	db_append_string(&stmt, buf);

	if (db_execute_immediate(driver, &stmt) != DB_OK) {
	    G_warning(_("Unable to insert new record: '%s'"),
		      db_get_string(&stmt));
	}
    }
    point_cat++;
}
