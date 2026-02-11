clear_result(RecogProcess *r)
{
#ifdef WORD_GRAPH

  wordgraph_clean(&(r->result.wg1));
#endif

  if (r->lmvar == LM_DFA_WORD) {
    if (r->result.status == J_RESULT_STATUS_SUCCESS) {

      free(r->result.sent);
    }
  } else {
    if (r->graphout) {
      if (r->config->graph.confnet) {

	cn_free_all(&(r->result.confnet));
      } else if (r->config->graph.lattice) {
      }

      wordgraph_clean(&(r->result.wg));
    }
    result_sentence_free(r);
  }
}
