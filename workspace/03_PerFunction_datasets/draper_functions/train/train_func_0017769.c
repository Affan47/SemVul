has_value(gchar *input)
{
    int have_value = 0;

    if( input!=NULL && strlen(input) > 2 )
      have_value = 1;

    return have_value;
}
