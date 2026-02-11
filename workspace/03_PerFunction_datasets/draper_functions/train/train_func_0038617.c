map_seqs(max_group, total_motifs, motif)
int max_group, total_motifs;
struct motif_struct *motif;
{
  struct group_struct *groups;
  int i, j, x, group_no;

  groups = (struct group_struct *)
	      malloc(sizeof(struct group_struct) * total_motifs);
  if (groups == NULL) {
	printf("Couldn't allocate GROUPS.\n");
	exit(-1);
	}

  for (x = 0; x < NumSeqs; x++)  {
    group_no = 0;
    for (i = 0; i < total_motifs; i++)
      for (j = 0; j < motif[i].freq; j++)
	if (motif[i].seq_no[j] == x) {
	  groups[group_no].position = motif[i].pos[j];
	  groups[group_no].group_no = motif[i].group;
	  groups[group_no++].sub_no = motif[i].sub_group;
	  }
    if (group_no > 0) {
      qsort(groups, group_no, sizeof(struct group_struct), compare_groups);
      i = group_no;
      for (group_no = 0, j = 1; j < i; j++)
	if (groups[group_no].group_no == groups[j].group_no &&
	    groups[j].position - groups[group_no].position < 12)
	  groups[group_no].sub_no = 0;
	else { groups[++group_no].position = groups[j].position;
	       groups[group_no].group_no = groups[j].group_no;
	       groups[group_no].sub_no = groups[j].sub_no;}
      group_no++;
      }

    printf("                    Protein %s:\n", Seqname[x]);

    j = -1;
    for (i = 0; i < group_no; i++)  {
      for (j++; j < groups[i].position / 6; j++) printf(".");
      if (groups[i].group_no <= max_group) printf("%d",groups[i].group_no);
	else printf(".");
      if (groups[i].sub_no > 0) printf("%c",(char) groups[i].sub_no + 64);
      }
    for (j++; j < Len[x] / 6; j++) printf(".");
    printf(" %d\n\n",Len[x]);
    }
   free(groups);
}
