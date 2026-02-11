ExtendSolidArea(rfbClientPtr cl,
                int x,
                int y,
                int w,
                int h,
                uint32_t colorValue,
                int *x_ptr,
                int *y_ptr,
                int *w_ptr,
                int *h_ptr)
{
    int cx, cy;


    for ( cy = *y_ptr - 1;
          cy >= y && CheckSolidTile(cl, *x_ptr, cy, *w_ptr, 1, &colorValue, TRUE);
          cy-- );
    *h_ptr += *y_ptr - (cy + 1);
    *y_ptr = cy + 1;


    for ( cy = *y_ptr + *h_ptr;
          cy < y + h &&
              CheckSolidTile(cl, *x_ptr, cy, *w_ptr, 1, &colorValue, TRUE);
          cy++ );
    *h_ptr += cy - (*y_ptr + *h_ptr);


    for ( cx = *x_ptr - 1;
          cx >= x && CheckSolidTile(cl, cx, *y_ptr, 1, *h_ptr, &colorValue, TRUE);
          cx-- );
    *w_ptr += *x_ptr - (cx + 1);
    *x_ptr = cx + 1;


    for ( cx = *x_ptr + *w_ptr;
          cx < x + w &&
              CheckSolidTile(cl, cx, *y_ptr, 1, *h_ptr, &colorValue, TRUE);
          cx++ );
    *w_ptr += cx - (*x_ptr + *w_ptr);
}
