collisionWithNodeHelper(double r, double ix, double iy, double iz, double ir)
{
    if((x-ix)*(x-ix)+(y-iy)*(y-iy)+(z-iz)*(z-iz)>=(r+ir)*(r+ir))
    {
        return false;
    }
    return true;
}
