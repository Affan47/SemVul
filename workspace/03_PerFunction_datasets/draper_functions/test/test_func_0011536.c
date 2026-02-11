show_frame(int imagenumber, int usename)
{
  Gif_Image *gfi;
  Gt_Frame *frame;

  if (!input || !(gfi = Gif_GetImage(input, imagenumber)))
    return;

  switch (mode) {

   case MERGING:
   case INSERTING:
   case EXPLODING:
   case INFOING:
   case BATCHING:
    if (!frames_done)
      clear_frameset(frames, first_input_frame);
    frame = add_frame(frames, -1, input, gfi);
    if (usename)
      frame->explode_by_name = 1;
    break;

   case DELETING:
    frame = &FRAME(frames, first_input_frame + imagenumber);
    frame->use = 0;
    break;

  }

  next_frame = 0;
  frames_done = 1;
}
