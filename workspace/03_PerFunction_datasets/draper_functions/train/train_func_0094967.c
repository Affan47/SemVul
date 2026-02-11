fdlg_delete( FDlg **fdlg )
{
    if ( *fdlg ) {
        group_delete( &(*fdlg)->group );
        lbox_delete( &(*fdlg)->lbox );
        free_surf( &(*fdlg)->info_buffer );
        free( *fdlg ); *fdlg = 0;
    }
}
