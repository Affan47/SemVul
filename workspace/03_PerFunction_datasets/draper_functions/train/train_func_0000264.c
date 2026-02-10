ConvertPathtype(xe,ye,xb,yb,width,togds)

int *xe,*ye;
int xb,yb;
int width;
int togds;
{
    double angle;
    double deltaX,deltaY;

    if (width == 0) return;
    if (width < 0) width = -width;
    width /= 2;
    if (togds) {
        if (*xe == xb) {
            if (*ye > yb)
                *ye += width;
            else
                *ye -= width;
        }
        else if (*ye == yb) {
            if (*xe > xb)
                *xe += width;
            else
                *xe -= width;
        }
        else {
            deltaX = (double)(*xe - xb);
            deltaY = (double)(*ye - yb);
            angle = atan2(deltaY,deltaX);
            deltaX = (double)(width) * cos(angle);
            deltaY = (double)(width) * sin(angle);
            *xe += (int)(deltaX);
            *ye += (int)(deltaY);
        }
    }
    else {
        if (*xe == xb) {
            if (*ye > yb)
                *ye -= width;
            else
                *ye += width;
        }
        else if (*ye == yb) {
            if (*xe > xb)
                *xe -= width;
            else
                *xe += width;
        }
        else {
            deltaX = (double)(*xe - xb);
            deltaY = (double)(*ye - yb);
            angle = atan2(deltaY,deltaX);
            deltaX = (double)(width) * cos(angle);
            deltaY = (double)(width) * sin(angle);
            *xe -= (int)(deltaX);
            *ye -= (int)(deltaY);
        }
    }
}
