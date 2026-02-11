assign_costs(struct csa *csa)
{
      struct arcs *arc_ptr = arc_list;
      int (*random)(struct csa *csa, double *);
      int i;

      int high_cost;

      int max_cost = 0;

      switch (arc_costs.distribution)
      {  case UNIFORM:
            random = uniform;
            break;
         case EXPONENTIAL:
            random = exponential;
            break;
         default:
            xassert(csa != csa);
      }

      for (i = n_source + n_sink; i < n_grid_arc; i++, arc_ptr++)
      {  arc_ptr->cost = random(csa, arc_costs.parameter);
         if (max_cost < arc_ptr->cost) max_cost = arc_ptr->cost;
      }
      i = i - n_source - n_sink;

      high_cost = max_cost * 2;
      for (; i < n_grid_arc; i++, arc_ptr++)
         arc_ptr->cost = high_cost;

      for (; i < n_arc; i++, arc_ptr++)
         arc_ptr->cost = random(csa, arc_costs.parameter);
      return;
}
