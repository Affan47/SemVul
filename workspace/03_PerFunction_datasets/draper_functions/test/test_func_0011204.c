cson_array_clean( cson_array * ar, char properlyCleanValues )
{
    if( ar )
    {
        unsigned int i = 0;
        cson_value * val = NULL;
        for( ; i < ar->list.count; ++i )
        {
            val = ar->list.list[i];
            if(val)
            {
                ar->list.list[i] = NULL;
                if( properlyCleanValues )
                {
                    cson_value_free( val );
                }
            }
        }
        cson_value_list_reserve(&ar->list,0);
        ar->list = cson_value_list_empty


            ;
    }
}
