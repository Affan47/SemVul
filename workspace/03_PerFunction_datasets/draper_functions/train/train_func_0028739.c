_actionFinalizedCB( gpointer data, GObject *where_the_object_was )
{
    if ( data && where_the_object_was ) {
        UnitTracker* self = reinterpret_cast<UnitTracker*>(data);
        self->_actionFinalized( where_the_object_was );
    }
}
