img_set_style(argc, argv, img)
    int argc;
    VALUE *argv;
    VALUE img;
{
    gdImagePtr im;
    int *style;
    int i;

    Data_Get_Struct(img, gdImage, im);
    style = ALLOCA_N(int, argc);
    for (i=0; i<argc; i++) {
	style[i] = NUM2INT(argv[i]);
    }

    gdImageSetStyle(im, style, argc);

    return img;
}
