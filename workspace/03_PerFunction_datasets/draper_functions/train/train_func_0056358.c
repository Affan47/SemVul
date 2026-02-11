createFlip(const int horz,
                                  const int vert) const
{
    DiImage *image = new DiMono1Image(this, horz, vert);
    return image;
}
