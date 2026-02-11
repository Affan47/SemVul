IDirectFBSurface_GetSubSurface( IDirectFBSurface    *thiz,
                                const DFBRectangle  *rect,
                                IDirectFBSurface   **surface )
{
     DFBResult ret;

     DIRECT_INTERFACE_GET_DATA(IDirectFBSurface)

     D_DEBUG_AT( Surface, "%s( %p )\n", __FUNCTION__, thiz );


     if (!data->surface)
          return DFB_DESTROYED;

     if (!surface)
          return DFB_INVARG;


     DIRECT_ALLOCATE_INTERFACE( *surface, IDirectFBSurface );

     if (rect || data->limit_set) {
          DFBRectangle wanted, granted;


          if (rect) {
               wanted = *rect;

               wanted.x += data->area.wanted.x;
               wanted.y += data->area.wanted.y;

               if (wanted.w <= 0 || wanted.h <= 0) {
                    wanted.w = 0;
                    wanted.h = 0;
               }
          }
          else {
               wanted = data->area.wanted;
          }


          granted = wanted;

          dfb_rectangle_intersect( &granted, &data->area.granted );


          ret = IDirectFBSurface_Construct( *surface, thiz,
                                            &wanted, &granted, &data->area.insets,
                                            data->surface,
                                            data->caps | DSCAPS_SUBSURFACE, data->core );
     }
     else {

          ret = IDirectFBSurface_Construct( *surface, thiz,
                                            NULL, NULL, &data->area.insets,
                                            data->surface,
                                            data->caps | DSCAPS_SUBSURFACE, data->core );
     }

     return ret;
}
