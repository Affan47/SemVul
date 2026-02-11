write_scanline_exr (const float       *pixels,
                    int                w,
                    int                h,
                    int                d,
                    const std::string &filename)
{
  Imf::Header header (create_header (w, h, d));
  Imf::OutputFile out (filename.c_str (), header);
  Imf::FrameBuffer fbuf (create_frame_buffer (w, h, d, pixels));
  out.setFrameBuffer (fbuf);
  out.writePixels (h);
}
