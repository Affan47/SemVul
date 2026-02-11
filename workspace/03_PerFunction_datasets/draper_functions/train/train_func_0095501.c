get_row_size()
{
    if( ! get_model() ) return 0;

    return get_model()->children().size();
}
