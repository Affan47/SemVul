cson_kvp_list_visit( cson_kvp_list * self,

                        int (*visitor)(cson_kvp * obj, void * visitorState ),


                        void * visitorState )
{
    int rc = cson_rc.ArgError;
    if( self && visitor )
    {
        unsigned int i = 0;
        for( rc = 0; (i < self->count) && (0 == rc); ++i )
        {

            cson_kvp * obj = self->list[i];


            if(obj) rc = visitor( obj, visitorState );
        }
    }
    return rc;
}
