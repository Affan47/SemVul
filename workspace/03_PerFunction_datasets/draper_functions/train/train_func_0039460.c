find_frame_left (rp_frame *frame)
{
  rp_screen *s = frames_screen (frame);
  rp_frame *cur;

  list_for_each_entry (cur, &s->frames, node)
    {
      if (frame->x == cur->x + cur->width)
        {
          if (frame->y >= cur->y && frame->y < cur->y + cur->height)
            return cur;
        }
    }

  return NULL;
}
