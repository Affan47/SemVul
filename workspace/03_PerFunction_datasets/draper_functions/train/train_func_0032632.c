tree_bits (bool_t child, unsigned level, const tree_t *model)


{
   real_t prob = model->counts [level] / (real_t) model->total [level];

   return child ? - log2 (prob) : - log2 (1 - prob);
}
