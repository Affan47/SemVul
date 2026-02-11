gsb_data_report_get_structure ( gint report_number )
{
    GSList *tmp_list;


    if ( report_buffer
	 &&
	 report_buffer -> report_number == report_number )
	return (gpointer) report_buffer;

    tmp_list = report_list;

    while ( tmp_list )
    {
	struct_report *report;

	report = tmp_list -> data;

	if ( report -> report_number == report_number )
	{
	    report_buffer = report;
	    return report;
	}

	tmp_list = tmp_list -> next;
    }


    return NULL;
}
