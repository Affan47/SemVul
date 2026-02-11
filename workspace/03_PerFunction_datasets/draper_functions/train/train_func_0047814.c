parse_date(const Glib::ustring& text, const std::locale& locale, bool& success)
{


  typedef std::stringstream type_stream;


  tm the_c_time;
  memset(&the_c_time, 0, sizeof(the_c_time));


  const bool is_iso_locale = (locale == std::locale::classic());
  const bool skip_time_get = !is_iso_locale && (strcmp(GLOM_NON_TRANSLATED_LOCALE_DATE_FORMAT, glom_get_locale_date_format()) != 0);

  std::ios_base::iostate err = std::ios_base::goodbit;

  if(!skip_time_get)
  {

    type_stream the_stream;
    the_stream.imbue(locale);
    the_stream << text;


    typedef std::time_get<char> type_time_get;
    typedef type_time_get::iter_type type_iterator;

    const type_time_get& tg = std::use_facet<type_time_get>(locale);

    type_iterator the_begin(the_stream);
    type_iterator the_end;

    tg.get_date(the_begin, the_end, the_stream, err, &the_c_time);
  }
  else
  {

  }

  if(!skip_time_get && err != std::ios_base::failbit)
  {
    success = true;
  }
  else
  {


    Glib::Date date;
    date.set_parse(text);
    if(date.valid())
    {

      tm null_c_time;
      memset(&null_c_time, 0, sizeof(null_c_time));

      the_c_time = null_c_time;

      if(date.get_year() != Glib::Date::BAD_YEAR)
        the_c_time.tm_year = date.get_year() - 1900;

      if(date.get_month() != Glib::Date::BAD_MONTH)
        the_c_time.tm_mon = date.get_month() - 1;

      if(date.get_day() != Glib::Date::BAD_DAY)
        the_c_time.tm_mday = date.get_day();

      success = true;
    }
    else
    {


      tm blank_time;
      memset(&blank_time, 0, sizeof(blank_time));

      blank_time.tm_mday = 1;
      blank_time.tm_mon = 1;
      the_c_time = blank_time;
      success = false;
    }
  }


  if(the_c_time.tm_mday == 0)
    the_c_time.tm_mday = 1;


  return the_c_time;
}
