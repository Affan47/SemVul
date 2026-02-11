getcoreExonnodefromSA(GthSA *sa, unsigned long exonindex)
{
  Exonnode node;
  Exonscoreinfo scoreinfo;


  gt_assert(gth_sa_num_of_exons(sa));

  gt_assert(gth_sa_num_of_exons(sa) - 1 ==
         gth_sa_num_of_introns(sa));

  gt_assert(exonindex < gth_sa_num_of_exons(sa));

  node.exonscores = gt_array_new(sizeof (Exonscoreinfo));

  node.range.start = gth_sa_get_exon(sa, exonindex)->leftgenomicexonborder;
  node.range.end = gth_sa_get_exon(sa, exonindex)->rightgenomicexonborder;

  if (exonindex == 0)
    node.leftmergeable = true;
  else
    node.leftmergeable = false;

  if (exonindex == gth_sa_num_of_exons(sa) - 1) {

    node.rightmergeable = true;
  }
  else
    node.rightmergeable = false;


  if (exonindex < gth_sa_num_of_exons(sa) - 1) {

    node.successorintron = gth_sa_get_intron(sa, exonindex);
  }
  else {

    node.successorintron = NULL;
  }


  scoreinfo.exonscore = gth_sa_get_exon(sa, exonindex)->exonscore;
  scoreinfo.lengthofscoringexon = node.range.end - node.range.start + 1;

  gt_array_add(node.exonscores, scoreinfo);

  return node;
}
