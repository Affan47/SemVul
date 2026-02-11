find_handler (gpointer find_data, gpointer user_data)
{
    BillTermsWindow *btw = user_data;
    QofBook *book = find_data;

    return (btw != NULL && btw->book == book);
}
