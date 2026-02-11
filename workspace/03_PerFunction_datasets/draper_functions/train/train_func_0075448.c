htnotify(DocumentRef &ref)
{
    char	*date = ref.DocNotification();
    char	*email = ref.DocEmail();

    if (date && *date && email && *email)
    {
	if (verbose > 2)
	{
	    cout << "Saw a date:" << endl;
	    cout << "Date:    " << date << endl;
	    cout << "URL:     " << ref.DocURL() << endl;
	    cout << "Subject: " << ref.DocSubject() << endl;
	    cout << "Email:   " << email << endl;
	    cout << endl;
	}

	int		month, day, year;
	if (!parse_date(date, year, month, day))
	{

	    if (verbose > 2)
	    {
		cout << "Malformed date: " << date << endl;
	    }

	    add_notification(date, email, ref.DocURL(), "Malformed Date");
	    return;
	}

	year -= 1900;
	month--;


	if (year < today->tm_year ||
	    (year == today->tm_year && month < today->tm_mon) ||
	    (year == today->tm_year && month == today->tm_mon &&
	     day < today->tm_mday))
	{


	    add_notification(date, email, ref.DocURL(), ref.DocSubject());
	}
	else
	{

	    if (verbose > 2)
	    {
		cout << "htnotify: URL " << ref.DocURL()
		     << " (" << year+1900 << "-" << month+1
		     << "-" << day << ")" << endl;
	    }
	}
    }
}
