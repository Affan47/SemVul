img_filled_polygon(img, ply, c)
    VALUE img;
    struct RArray *ply;
    VALUE c;
{
    gdImagePtr im;
    gdPointPtr pnt;
    int i, len;

    Data_Get_Struct(img, gdImage, im);

    poly_req(ply);
    len = RARRAY_LEN(ply)/2;
    pnt = ALLOCA_N(gdPoint, len);
    for (i=0; i<len; i++) {
	pnt[i].x = NUM2INT(RARRAY_PTR(ply)[i*2]);
	pnt[i].y = NUM2INT(RARRAY_PTR(ply)[i*2+1]);
    }

    gdImageFilledPolygon(im, pnt, len, NUM2INT(c));

    return img;
}
