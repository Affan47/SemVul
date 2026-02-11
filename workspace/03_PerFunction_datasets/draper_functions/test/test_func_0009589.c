gt_hmm_get_transition_probability(const GtHMM *hmm,
                                      unsigned int from_state_num,
                                      unsigned int to_state_num)
{
  gt_assert(hmm);
  gt_assert(from_state_num < hmm->num_of_states);
  gt_assert(to_state_num < hmm->num_of_states);
  if (hmm->transition_prob[from_state_num][to_state_num] == MINUSINFINITY)
    return 0.0;
  return exp(hmm->transition_prob[from_state_num][to_state_num]);
}
