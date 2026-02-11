gsds_get_typbuff(int id, IFLAG change_flag)
{
    dataset *ds;

    if ((ds = get_dataset(id))) {
	ds->changed = ds->changed | change_flag;
	ds->need_reload = 0;

	return (&(ds->databuff));
    }

    return (NULL);
}
