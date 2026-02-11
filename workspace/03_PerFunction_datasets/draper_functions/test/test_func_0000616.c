GIOgetDirData(GIOControl *gc) {

    if ( gc->direntrydata )
return( gc->iodata );

return( NULL );
}
