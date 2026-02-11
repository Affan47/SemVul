NPolyListBound(NPolyList *np, Transform T, TransformN *TN)
{
  BBox *result;
  int n, pdim;
  HPoint3 min, max, tmp, clean;
  HPointN ptN[1];

  n = np->n_verts;
  pdim = np->pdim;
  ptN->v = np->v;
  ptN->dim = pdim;


  if (!T && !TN) {
    HPointN *min = HPtNCreate(pdim, np->v);
    HPointN *max;

    HPtNDehomogenize(min, min);
    max = HPtNCopy(min, NULL);
    while(--n > 0) {
      ptN->v += pdim;
      HPtNMinMax(min, max, ptN);
    }
    result = (BBox *)GeomCCreate(NULL, BBoxMethods(),
				 CR_NMIN, min, CR_NMAX, max, CR_END);
    HPtNDelete(min);
    HPtNDelete(max);

    return result;
  }

  if (TN) {

    HPointN *minN;
    HPointN *maxN;
    HPointN *clean;
    BBox *result;

    minN = HPtNTransform(TN, ptN, NULL);
    HPtNDehomogenize(minN, minN);
    maxN = HPtNCopy(minN, NULL);

    clean = HPtNCreate(np->pdim, NULL);
    while(--n > 0) {
      ptN->v += pdim;
      HPtNTransform(TN, ptN, clean);
      HPtNMinMax(minN, maxN, clean);
    }
    result = (BBox *)GeomCCreate(NULL, BBoxMethods(),
				 CR_NMIN, minN, CR_NMAX, maxN, CR_END);

    HPtNDelete(minN);
    HPtNDelete(maxN);
    HPtNDelete(clean);

    return result;
  }


  if (T) {

    HPtNToHPt3(ptN, NULL, &min);
    HPt3Transform(T, &min, &min);
    HPt3Dehomogenize(&min, &min);
    max = min;
    while(--n > 0) {
      ptN->v += pdim;
      HPtNToHPt3(ptN, NULL, &tmp);
      HPt3Transform(T, &tmp, &clean);
      HPt3Dehomogenize(&clean, &clean);
      Pt3MinMax(&min, &max, &clean);
    }


    return (BBox *)GeomCCreate(NULL, BBoxMethods(),
			       CR_4MIN, &min, CR_4MAX, &max, CR_END);
  }

  return NULL;
}
