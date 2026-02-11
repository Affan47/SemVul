dfb_clipboard_core_initialize( CoreDFB                *core,
                               DFBClipboardCore       *data,
                               DFBClipboardCoreShared *shared )
{
     D_DEBUG_AT( Core_Clipboard, "dfb_clipboard_core_initialize( %p, %p, %p )\n", core, data, shared );

     D_ASSERT( data != NULL );
     D_ASSERT( shared != NULL );

     data->core   = core;
     data->shared = shared;

     shared->shmpool = dfb_core_shmpool( core );

     fusion_skirmish_init( &shared->lock, "Clipboard Core", dfb_core_world(core) );

     D_MAGIC_SET( data, DFBClipboardCore );
     D_MAGIC_SET( shared, DFBClipboardCoreShared );

     return DFB_OK;
}
