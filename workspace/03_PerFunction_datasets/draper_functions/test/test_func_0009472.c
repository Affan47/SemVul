error_in_grammar(int n, int line_no)
{
     switch (n) {
     case HINSI_ERROR:
	  fprintf(stderr, "\nparse error at line %d\n", line_no);
	  fprintf(stderr, "\ttoo many classfication.\n");
	  my_exit(GramError);
	  break;
     case BUNRUI_ERROR:
	  fprintf(stderr, "\nparse error at line %d\n", line_no);
	  fprintf(stderr, "\ttoo many sub-classfication.\n");
	  my_exit(GramError);
	  break;
     default:
	  fprintf(stderr, "\nparse error at line %d\n", line_no);
	  my_exit(GramError);
	  break;
     }
}
