dfb_gfxcard_find_driver( CoreDFB *core )
{
     DirectLink          *link;
     FusionSHMPoolShared *pool = dfb_core_shmpool( core );

     direct_list_foreach (link, dfb_graphics_drivers.entries) {
          DirectModuleEntry *module = (DirectModuleEntry*) link;

          const GraphicsDriverFuncs *funcs = direct_module_ref( module );

          if (!funcs)
               continue;

          if (!card->module && funcs->Probe( card )) {
               funcs->GetDriverInfo( card, &card->shared->driver_info );

               card->module       = module;
               card->driver_funcs = funcs;

               card->shared->module_name = SHSTRDUP( pool, module->name );
          }
          else
               direct_module_unref( module );
     }
}
