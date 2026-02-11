alternateaxes(vertex *sortarray, int arraysize, int axis)
#else
void alternateaxes(sortarray, arraysize, axis)
vertex *sortarray;
int arraysize;
int axis;
#endif

{
  int divider;

  divider = arraysize >> 1;
  if (arraysize <= 3) {


    axis = 0;
  }

  vertexmedian(sortarray, arraysize, divider, axis);

  if (arraysize - divider >= 2) {
    if (divider >= 2) {
      alternateaxes(sortarray, divider, 1 - axis);
    }
    alternateaxes(&sortarray[divider], arraysize - divider, 1 - axis);
  }
}
