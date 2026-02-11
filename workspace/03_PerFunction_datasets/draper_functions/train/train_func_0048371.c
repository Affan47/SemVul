p_pview_repaint_desaturated(GapPView *pv_ptr)
{
  if(gap_debug)
  {
    printf("p_pview_repaint_desaturated START\n");
  }
  if(pv_ptr->pv_desaturated_area_data)
  {
    gdk_draw_rgb_image ( pv_ptr->da_widget->window
                       , pv_ptr->da_widget->style->white_gc
                       , 0
                       , 0
                       , pv_ptr->pv_width
                       , pv_ptr->pv_height
                       , GDK_RGB_DITHER_NORMAL
                       , pv_ptr->pv_desaturated_area_data
                       , pv_ptr->pv_width * 3
                       );
  }

}
