IpBlasDdot(Index size, const Number *x, Index incX, const Number *y,
                    Index incY)
  {
    if (incX > 0 && incY > 0)
    {
      ipfint n=size, INCX=incX, INCY=incY;

      return F77_FUNC(ddot,DDOT)(&n, x, &INCX, y, &INCY);
    }
    else
    {
      Number s = 0.0;

      for (; size; --size, x += incX, y += incY)
        s += *x * *y;

      return s;
    }
  }
