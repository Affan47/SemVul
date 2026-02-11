scroll_to_line(int line)
{

   GlyphIndex new_start, new_end;
   GlyphIndex max_end = te_buffer_->lines();
   if (line < 0)
      new_start = 0;
   else if (max_end - line < lines_)
      new_start = max_end - lines_;
   else
      new_start = line;
   new_end = new_start + lines_ - 1;

   if (new_start == start_row_)
      return;


   int line_width = text_editor_->GetShape()->vunits;
   int from_pix = int(start_row_ * line_width);
   int to_pix = int(new_start * line_width);
   int diff_pix = from_pix - to_pix;

   text_editor_->ScrollBy(0, diff_pix);
   start_row_ = new_start;
   end_row_ = new_end;
   notify();
}
