rescale()
{

  long i;
  double treeheight, treewidth, extrax, extray, temp;
  treeheight = maxy - miny;
  treewidth = maxx - minx;
  if (style == circular) {
    treewidth = 1.0;
    treeheight = 1.0;
    if (!rescaled) {
      if (uselengths) {
        labelheight *= (maxheight - rooty) / treedepth;
        topoflabels *= (maxheight - rooty) / treedepth;
        bottomoflabels *= (maxheight - rooty) / treedepth;
        leftoflabels *= (maxheight - rooty) / treedepth;
        rightoflabels *= (maxheight - rooty) / treedepth;
        treewidth *= (maxheight - rooty) / treedepth;
      }
    }
  }
  treewidth += rightoflabels + leftoflabels;
  treeheight += topoflabels + bottomoflabels;
  if (grows == vertical) {
    if (!rescaled)
      expand = bscale;
    else {
      expand = (xsize - 2 * xmargin) / treewidth;
      if ((ysize - 2 * ymargin) / treeheight < expand)
        expand = (ysize - 2 * ymargin) / treeheight;
    }
    extrax = (xsize - 2 * xmargin - treewidth * expand) / 2.0;
    extray = (ysize - 2 * ymargin - treeheight * expand) / 2.0;
  } else {
    if (!rescaled)
      expand = bscale;
    else {
      expand = (ysize - 2 * ymargin) / treewidth;
      if ((xsize - 2 * xmargin) / treeheight < expand)
        expand = (xsize - 2 * xmargin) / treeheight;
    }
    extrax = (xsize - 2 * xmargin - treeheight * expand) / 2.0;
    extray = (ysize - 2 * ymargin - treewidth * expand) / 2.0;
  }
  for (i = 0; i < nextnode; i++) {
    nodep[i]->xcoord = expand * (nodep[i]->xcoord + leftoflabels);
    nodep[i]->ycoord = expand * (nodep[i]->ycoord + bottomoflabels);
    if ((style != circular) && (grows == horizontal)) {
      temp = nodep[i]->ycoord;
      nodep[i]->ycoord = expand * treewidth - nodep[i]->xcoord;
      nodep[i]->xcoord = temp;
    }
    nodep[i]->xcoord += xmargin + extrax;
    nodep[i]->ycoord += ymargin + extray;
  }
  if (style == circular) {
    xx0 = xmargin+extrax+expand*(leftoflabels + 0.5);
    yy0 = ymargin+extray+expand*(bottomoflabels + 0.5);
  }
  else if (grows == vertical)
      rooty = ymargin + extray;
    else
      rootx = xmargin + extrax;
}
