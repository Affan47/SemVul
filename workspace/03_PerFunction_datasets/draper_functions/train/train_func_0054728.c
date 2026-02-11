img_color_closest_tri(img, r, g, b)
    VALUE img, r, g, b;
{
    gdImagePtr im;
    int c;

    Data_Get_Struct(img, gdImage, im);
    c = gdImageColorClosest(im, NUM2INT(r), NUM2INT(g), NUM2INT(b));

    return INT2FIX(c);
}
