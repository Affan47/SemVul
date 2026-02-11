IDirectFBSurface_FillRectangles( IDirectFBSurface   *thiz,
                                 const DFBRectangle *rects,
                                 unsigned int        num_rects )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBSurface)

     D_DEBUG_AT( Surface, "%s( %p, %p [%d] )\n", __FUNCTION__, thiz, rects, num_rects );

     DFB_RECTANGLES_DEBUG_AT( Surface, rects, num_rects );


     if (!data->surface)
          return DFB_DESTROYED;


     if (!data->area.current.w || !data->area.current.h)
          return DFB_INVAREA;

     if (data->locked)
          return DFB_LOCKED;

     if (!rects || !num_rects)
          return DFB_INVARG;

     if (data->area.wanted.x || data->area.wanted.y) {
          unsigned int  i;
          DFBRectangle *local_rects;
          bool          malloced = (num_rects > 256);

          if (malloced)
               local_rects = D_MALLOC( sizeof(DFBRectangle) * num_rects );
          else
               local_rects = alloca( sizeof(DFBRectangle) * num_rects );

          for (i=0; i<num_rects; i++) {
               local_rects[i].x = rects[i].x + data->area.wanted.x;
               local_rects[i].y = rects[i].y + data->area.wanted.y;
               local_rects[i].w = rects[i].w;
               local_rects[i].h = rects[i].h;
          }

          dfb_gfxcard_fillrectangles( local_rects, num_rects, &data->state );

          if (malloced)
               D_FREE( local_rects );
     }
     else
          dfb_gfxcard_fillrectangles( rects, num_rects, &data->state );

     return DFB_OK;
}
