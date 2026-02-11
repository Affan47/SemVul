or_circuit_new(circid_t p_circ_id, or_connection_t *p_conn)
{

  or_circuit_t *circ;

  circ = tor_malloc_zero(sizeof(or_circuit_t));
  circ->_base.magic = OR_CIRCUIT_MAGIC;

  if (p_conn)
    circuit_set_p_circid_orconn(circ, p_circ_id, p_conn);

  circ->remaining_relay_early_cells = MAX_RELAY_EARLY_CELLS_PER_CIRCUIT;

  init_circuit_base(TO_CIRCUIT(circ));


  circ->p_cell_ewma.cell_count = 0.0;
  circ->p_cell_ewma.last_adjusted_tick = cell_ewma_get_tick();
  circ->p_cell_ewma.is_for_p_conn = 1;


  circ->p_cell_ewma.heap_index = -1;

  return circ;
}
