IDirectFB_CreateFont( IDirectFB                 *thiz,
                      const char                *filename,
                      const DFBFontDescription  *desc,
                      IDirectFBFont            **interface )
{
     DFBResult                   ret;
     DirectInterfaceFuncs       *funcs = NULL;
     IDirectFBFont              *font;
     IDirectFBFont_ProbeContext  ctx;

     DIRECT_INTERFACE_GET_DATA(IDirectFB)

     D_DEBUG_AT( IDFB, "%s( %p, '%s' )\n", __FUNCTION__, thiz, filename );


     if (!interface)
          return DFB_INVARG;

     if (desc) {
          if ((desc->flags & DFDESC_HEIGHT) && desc->height < 1)
               return DFB_INVARG;

          if ((desc->flags & DFDESC_WIDTH) && desc->width < 1)
               return DFB_INVARG;
     }

     if (filename) {
          if (!desc)
               return DFB_INVARG;

          if (access( filename, R_OK ) != 0)
               return errno2result( errno );
     }


     ctx.filename = filename;


     ret = DirectGetInterface( &funcs, "IDirectFBFont", NULL, DirectProbeInterface, &ctx );
     if (ret)
          return ret;

     DIRECT_ALLOCATE_INTERFACE( font, IDirectFBFont );


     ret = funcs->Construct( font, data->core, filename, desc );
     if (ret)
          return ret;

     *interface = font;

     return DFB_OK;
}
