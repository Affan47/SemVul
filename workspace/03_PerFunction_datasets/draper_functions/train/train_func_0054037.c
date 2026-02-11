cell_ewma_to_circuit(cell_ewma_t *ewma)
{
  if (ewma->is_for_p_conn) {

    or_circuit_t *orcirc = SUBTYPE_P(ewma, or_circuit_t, p_cell_ewma);
    return TO_CIRCUIT(orcirc);
  } else {

    return SUBTYPE_P(ewma, circuit_t, n_cell_ewma);
  }
}
