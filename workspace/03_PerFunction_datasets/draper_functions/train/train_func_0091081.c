getExactHeight (float x, float z)
{
  if (gridstep == 2) return getExactHeight2 (x, z);
  else if (gridstep == 3) return getExactHeight3 (x, z);
  else if (gridstep == 4) return getExactHeight4 (x, z);
  float mx = x;
  float mz = z;
  int mx1 = (int) floor (mx);
  int mz1 = (int) floor (mz);
  int mx2 = mx1 + 1;
  int mz2 = mz1 + 1;
  int ax1 = GETCOORD(mx1);
  int ax2 = GETCOORD(mx2);
  int az1 = GETCOORD(mz1);
  int az2 = GETCOORD(mz2);
  float h2 = (float)hw[ax1][az1]*((float)mx2-mx)*((float)mz2-mz) + (float)hw[ax2][az1]*(mx-mx1)*((float)mz2-mz) +
             (float)hw[ax1][az2]*((float)mx2-mx)*(mz-mz1) + (float)hw[ax2][az2]*(mx-mx1)*(mz-mz1);
  return (ZOOM * (h2*zoomz - zoomz2));
}
