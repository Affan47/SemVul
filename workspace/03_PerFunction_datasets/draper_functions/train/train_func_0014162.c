in_back(ta,tb)
struct tsort *ta,*tb;
{
  int n;

  int retval;

  if ( verbose_flag )
  {
    in_back_calls++;
    if ( (ta->flag & 0xF) == FACET  )
    { if ( (tb->flag & 0xF) == FACET  )
        facetfacet++;
      else facetedge++;
    }
    else
    { if ( (tb->flag & 0xF) == FACET  )
        facetedge++;
      else edgeedge++;
    }
  }


  if ( ((ta->quadcode & tb->quadcode) != ta->quadcode) &&
       ((ta->quadcode & tb->quadcode) != tb->quadcode) )
    return DISJOINT;


  for ( n = 0 ; n < 2 ; n++ )
     if ( (tb->maxs[n] <= ta->mins[n]) || (tb->mins[n] >= ta->maxs[n]) )
        return DISJOINT;
  if ( ta->maxs[2] <= tb->mins[2] ) return FIRST_BACK;

  box_overlaps++;

  if ( separating_line(ta,tb) == DISJOINT ) return DISJOINT;

  retval = plane_test(ta,tb);
  if ( retval & (FIRST_BACK|COPLANAR|DISJOINT) ) return retval;


#ifdef ZZZ
  if ( (ta->flag & 0xF) == FACET  )
  { if ( (tb->flag & 0xF) == FACET  )
      return facetfacetcompare(ta,tb);
     else
     {    retval = edgefacetcompare(tb,ta);
        if ( retval & (FIRST_BACK|SECOND_BACK) )
           return retval ^ (FIRST_BACK|SECOND_BACK);
        else return retval;
    }
  }
  else
  { if ( (tb->flag & 0xF) == FACET  )
      return edgefacetcompare(ta,tb);
    else
    { retval = edgeedgecompare(tb,ta);
      if ( retval & (FIRST_BACK|SECOND_BACK) )
           return retval ^ (FIRST_BACK|SECOND_BACK);
      else return retval;
    }

  }
#endif


  return retval;
}
