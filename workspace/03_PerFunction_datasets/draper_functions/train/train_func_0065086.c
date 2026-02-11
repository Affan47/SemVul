setNeighbours(arrayList *newTets)
{
  simplex *s, *s2;
  GwyDelaunayVertex *v1, *v2, *v3, *t1, *t2, *t3, *tmp;

  gint i, j, k;

  for (j=0; j<arrayListSize(newTets); j++)
  {
    s = getFromArrayList(newTets,j);


    v1 = s->p[0];
    v2 = s->p[1];
    v3 = s->p[2];


    for (k=0; k<arrayListSize(newTets); k++)
    {
      s2 = getFromArrayList(newTets,k);
      if (s == s2) continue;


      for (i=1; i<4; i++)
      {
        getFaceVerticies(s2, i, &t1, &t2, &t3, &tmp);


        if (      (v1 == t1 || v1 == t2 || v1 == t3) &&
                  (v2 == t1 || v2 == t2 || v2 == t3)    )
          s->s[1] = s2;
        else if ( (v2 == t1 || v2 == t2 || v2 == t3) &&
                  (v3 == t1 || v3 == t2 || v3 == t3)    )
          s->s[3] = s2;
        else if ( (v3 == t1 || v3 == t2 || v3 == t3) &&
                  (v1 == t1 || v1 == t2 || v1 == t3)    )
          s->s[2] = s2;
      }
    }
  }
}
