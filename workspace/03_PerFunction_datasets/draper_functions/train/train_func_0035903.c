facet_start_event(fe)
struct vis_event *fe;
{ REAL v1,v2;
  struct vis_conedge *spot;

  if ( visdebuglevel >= VIS_EVENTDUMP )
    printf("start edges %d %d  facet %d at %20.15f\n",
      fe->e1-vis_conedges,fe->e2-vis_conedges,
        fe->t-vis_list, (double)sweep_u);

PROF_START(facet_start_event)
  sweep_u = fe->time;
  v1 = activate_edge(fe->e1); fe->e1->use_count++;
  v2 = activate_edge(fe->e2); fe->e2->use_count++;

  if ( v2 < v1 )
  { kb_error(2505,"Internal: Visibility list insertion out of order.\n",
        WARNING);
    return -1;
  }

  if ( fe->e1->seqno > fe->e2->seqno )
  { kb_error(2508,"Internal: Visibility list insertion out of order.\n",
        WARNING);
    return -1;
  }


  for ( spot = fe->e1 ; spot != fe->e2 ; spot = spot->next_active )
  { if ( spot == NULL )
    { kb_error(2506,"Internal: Visibility list bad in facet_start_event().\n",
          WARNING);
      return -1;
    }
    add_layer(spot,fe->t);
  }
PROF_FINISH(facet_start_event)

  find_next_event(fe->e1);
  find_next_event(fe->e2);

  return 1;
}
