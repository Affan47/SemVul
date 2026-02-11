write_file(File *f)
{
	return( f->file_put_long(abs_scale) && !f->file_put_long(table_size)
		&& f->file_write(remap_table, table_size * (2*abs_scale+1)) );
}
