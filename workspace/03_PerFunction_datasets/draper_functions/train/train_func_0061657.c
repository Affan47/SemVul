unoptimized_frame(Gt_Viewer *viewer, int frame, int slow)
{

  if (!viewer->unoptimized_frames[frame].pixmap) {
    (void) Gif_XNextImage(viewer->gfx, viewer->gfs, frame,
			  viewer->unoptimized_frames);
    pixel_memory_kb += screen_memory_kb(viewer);
    viewer->unoptimized_frames[viewer->n_unoptimized_frames].user_data =
      frame;
    ++viewer->n_unoptimized_frames;
    if (slow) {
      set_viewer_name(viewer, frame);
      XFlush(viewer->display);
    }
  }


  while (pixel_memory_limit_kb != (unsigned) -1
         && pixel_memory_limit_kb < pixel_memory_kb
         && viewer->n_unoptimized_frames > 1) {
    int killidx, killframe, i = 0;
    do {
      killidx = random() % viewer->n_unoptimized_frames;
      killframe = viewer->unoptimized_frames[killidx].user_data;
      ++i;
    } while (killframe == frame
             || (i < 10 && killframe > frame && killframe < frame + 5)
             || (i < 10 && (killframe % 50) == 0));
    XFreePixmap(viewer->display, viewer->unoptimized_frames[killframe].pixmap);
    viewer->unoptimized_frames[killframe].pixmap = None;
    --viewer->n_unoptimized_frames;
    viewer->unoptimized_frames[killidx].user_data =
      viewer->unoptimized_frames[viewer->n_unoptimized_frames].user_data;
    pixel_memory_kb -= screen_memory_kb(viewer);
  }

  return viewer->unoptimized_frames[frame].pixmap;
}
