sbe_write_data_table( fsbe_context *cx, Data_table *dtp )
{
    switch( out_lang_tag ){
    case LANG_FORTRAN:
	fsbe_write_data_table( cx, dtp );
	break;
    default:
	break;
    }
}
