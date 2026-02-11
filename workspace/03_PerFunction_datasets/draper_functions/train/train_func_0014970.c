select_active_sheet (biff_workbook * workbook, unsigned int current_offset)
{

    biff_sheet *p_sheet;
    p_sheet = workbook->first_sheet;
    while (p_sheet)
      {
	  if (p_sheet->start_offset == current_offset)
	    {

		workbook->active_sheet = p_sheet;
		return;
	    }
	  p_sheet = p_sheet->next;
      }
    workbook->active_sheet = NULL;
}
