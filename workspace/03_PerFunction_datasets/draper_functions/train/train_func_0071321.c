complete_solution(struct partial_solution *soln,
			      const struct cm_state *state,
			      const struct tile_type_vector *lattice)
{
  int last_choice = -1;
  int i;

  if (soln->idle == 0) {
    return;
  }


  for (i = 0; i < num_types(state); i++) {
    if (soln->worker_counts[i] != 0) {
      last_choice = i;
    }
  }


  tile_type_vector_iterate(lattice, ptype) {
    int used = soln->worker_counts[ptype->lattice_index];
    int total = tile_type_num_tiles(ptype);
    int touse;

    if (ptype->lattice_index < last_choice) {


	continue;
    }
    if (!prereqs_filled(soln, ptype->lattice_index, state)) {

      continue;
    }

    touse = total - used;
    if (touse > soln->idle) {
      touse = soln->idle;
    }
    add_workers(soln, ptype->lattice_index, touse, state);

    if (soln->idle == 0) {

      return;
    }
  } tile_type_vector_iterate_end;
}
