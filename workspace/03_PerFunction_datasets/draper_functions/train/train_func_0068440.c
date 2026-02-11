floatCopyToBuffer(imageP I1, int row, int bufRowsRequired, float *buffer) {
    int height = I1->height;
    int width = I1->width;
    unsigned char *in;
    float *ptr;
    in = I1->image;

    int bufStartIndex = (row % bufRowsRequired) * width;

    ptr = &buffer[bufStartIndex+1];
    for (int x=0; x<width; x++) {
        ptr[0] = in[row*width+x];
        ptr++;
    }
}
