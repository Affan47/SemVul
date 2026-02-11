interpolated( const QImage &img1, const QImage &img2, int a1, int a2 )
{
    const int a = a1 + a2;
    if (!a)
        return img1.copy();

    QImage img( img1.size(), img1.format() );

    const uchar *src[2] = { img1.bits(), img2.bits() };
    uchar *dst = img.bits();
    const int n = img.width()*img.height()*4;
    for ( int i = 0; i < n; ++i )
    {
        *dst = ((*src[0]*a1 + *src[1]*a2)/a) & 0xff;
        ++dst; ++src[0]; ++src[1];
    }
    return img;
}
