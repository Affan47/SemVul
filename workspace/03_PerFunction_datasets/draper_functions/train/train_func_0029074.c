do_line_scanned(const Glib::ustring& line, guint line_number)
{

  if(line.empty())
   return;

  m_rows.push_back(CsvParser::type_row_strings());
  type_row_strings& row = m_rows.back();

  Glib::ustring field;


  Glib::ustring::const_iterator line_iter = CsvParser::advance_field(line.begin(), line.end(), field);
  row.push_back(field);


  while(line_iter != line.end())
  {

    ++line_iter;


    line_iter = advance_field(line_iter, line.end(), field);


    row.push_back(field);
  }

  signal_line_scanned().emit(row, line_number);
}
