show(nanodbc::result& results)
{
    const short columns = results.columns();
    long rows_displayed = 0;

    cout << "\nDisplaying " << results.affected_rows() << " rows "
         << "(" << results.rowset_size() << " fetched at a time):" << endl;


    cout << "row\t";
    for(short i = 0; i < columns; ++i)
        cout << results.column_name(i).c_str() << "\t";
    cout << endl;


    while(results.next())
    {
        cout << rows_displayed++ << "\t";
        for(short col = 0; col < columns; ++col)
			cout << "(" << results.get<nanodbc::string_type>(col, NANODBC_TEXT("null")).c_str() << ")\t";
        cout << endl;
    }
}
