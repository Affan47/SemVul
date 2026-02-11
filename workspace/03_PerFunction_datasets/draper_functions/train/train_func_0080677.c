_gsb_data_fyear_free ( struct_fyear *fyear )
{
    if ( ! fyear )
	return;
    if ( fyear -> fyear_name )
	g_free ( fyear -> fyear_name );
    if ( fyear -> beginning_date )
	g_date_free ( fyear -> beginning_date );
    if ( fyear -> end_date )
	g_date_free ( fyear -> end_date );
    g_free ( fyear );
    if ( fyear_buffer == fyear )
	fyear_buffer = NULL;
}
