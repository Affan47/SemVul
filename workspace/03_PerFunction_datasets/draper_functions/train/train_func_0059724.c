LoadFont(const char *path) {
  if (!path || !*path) return false;
  FILE *f = fopen(path, "r");
  if (f == NULL)
    return false;
  uint32_t codepoint;
  char buffer[1024];
  int dummy;
  Glyph tmp;
  Glyph *current_glyph = NULL;
  int row = 0;
  int x_offset = 0;
  int bitmap_shift = 0;
  while (fgets(buffer, sizeof(buffer), f)) {
    if (sscanf(buffer, "FONTBOUNDINGBOX %d %d %d %d",
               &dummy, &font_height_, &dummy, &base_line_) == 4) {
      base_line_ += font_height_;
    }
    else if (sscanf(buffer, "ENCODING %ud", &codepoint) == 1) {

    }
    else if (sscanf(buffer, "BBX %d %d %d %d", &tmp.width, &tmp.height,
                    &x_offset, &tmp.y_offset) == 4) {
      current_glyph = (Glyph*) malloc(sizeof(Glyph)
                                      + tmp.height * sizeof(rowbitmap_t));
      *current_glyph = tmp;


      bitmap_shift =
        8 * (sizeof(rowbitmap_t) - ((current_glyph->width + 7) / 8)) + x_offset;
      row = -1;
    }
    else if (strncmp(buffer, "BITMAP", strlen("BITMAP")) == 0) {
      row = 0;
    }
    else if (current_glyph && row >= 0 && row < current_glyph->height
             && (sscanf(buffer, "%x", &current_glyph->bitmap[row]) == 1)) {
      current_glyph->bitmap[row] <<= bitmap_shift;
      row++;
    }
    else if (strncmp(buffer, "ENDCHAR", strlen("ENDCHAR")) == 0) {
      if (current_glyph && row == current_glyph->height) {
        free(glyphs_[codepoint]);
        glyphs_[codepoint] = current_glyph;
        current_glyph = NULL;
      }
    }
  }
  fclose(f);
  return true;
}
