_disjoin_from_conn(dbi_result_t *result) {

  int idx;
  int found = -1;
  int retval;

  retval = result->conn->driver->functions->free_query(result);

  for (idx = 0; idx < result->conn->results_used; idx++) {
    if (found < 0) {

      if (result->conn->results[idx] == result) {
        found = idx;
        result->conn->results[idx] = NULL;
      }
    }
    else {

      result->conn->results[idx-1] = result->conn->results[idx];
    }
  }
  if (found >= 0) {
    result->conn->results[result->conn->results_used-1] = NULL;
    result->conn->results_used--;
  }

  result->conn = NULL;

  return retval;
}
