compare_origins (gconstpointer a,
                 gconstpointer b,
                 gpointer      user_data)
{
        const lglTemplateOrigin *a_origin = a, *b_origin = b;

        if ( a_origin->y < b_origin->y )
        {
                return -1;
        }
        else if ( a_origin->y > b_origin->y )
        {
                return +1;
        }
        else
        {
                if ( a_origin->x < b_origin->x )
                {
                        return -1;
                }
                else if ( a_origin->x > b_origin->x )
                {
                        return +1;
                }
                else
                {
                        return 0;
                }
        }
}
