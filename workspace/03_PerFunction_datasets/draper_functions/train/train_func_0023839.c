getCellData(unsigned int index, double* x, double* y, double* alt, double* probDev, double* cWidth, double* cHeight) const
{
    if(index >= numPoints || index<0)
    {
        return false;
    }
    *x = xCoors[index];
    *y = yCoors[index];
    *alt = altitudes[index];
    *probDev = probDeviation[index];
    *cWidth = cellWidth;
    *cHeight = cellHeight;
    return true;
}
