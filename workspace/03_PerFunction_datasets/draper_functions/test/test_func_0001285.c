clustered_weights(block)
     Block* block;
{
  double *seq_weight;


  int clust;
  int seq;

  int seq_num;


  double weight;


  CheckMem(
	   seq_weight = (double *) calloc(block->num_sequences, sizeof(double))
	   );


  seq_num = 0;
  for (clust=0; clust<block->num_clusters; clust++) {
    weight = 1.0/(double)block->clusters[clust].num_sequences;

    for (seq=seq_num; seq<seq_num+block->clusters[clust].num_sequences;
	 seq++) {
      seq_weight[seq] = weight;
    }
    seq_num += block->clusters[clust].num_sequences;
  }

  return seq_weight;
}
