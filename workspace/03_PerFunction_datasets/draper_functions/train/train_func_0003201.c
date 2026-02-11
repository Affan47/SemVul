print_phyloxml_tree(struct aln_tree_node* p,struct alignment* aln,FILE *fout)
{
	int j;

	if(p->links[0]){

		fprintf(fout,"<clade>\n");
		print_phyloxml_tree(p->links[0],aln,fout);
	}
	if(p->num < numseq){

		fprintf(fout,"<clade>\n<name>");
		for (j = 0; j < aln->lsn[p->num];j++){
			fprintf(fout,"%c",aln->sn[p->num][j]);
		}
		fprintf(fout,"</name>\n</clade>\n");


	}else{

	}
	if(p->links[1]){
		print_phyloxml_tree(p->links[1],aln,fout);
		fprintf(fout,"</clade>\n");
	}
}
