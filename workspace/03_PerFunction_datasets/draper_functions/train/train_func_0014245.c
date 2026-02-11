render (const GC &gc, int x, int y, const char *str)
{
    std::auto_ptr<Surface> s (render (str));
    if (s.get())
        blit (gc, x, y, s.get());
}
