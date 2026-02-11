main(int argc, char *argv[]) {
 long sloc;
 int i;
 FILE *file_list;
 char *s;

 total_sloc = 0;
 line_number = 1;

 if (argc <= 1) {
   sloc = sloc_count("-", stdin);
   printf("%ld %s\n", sloc, "-");
   total_sloc += sloc;
 } else if ((argc == 3) && (!strcmp(argv[1], "-f"))) {
   if (!strcmp (argv[2], "-")) {
     file_list = stdin;
   } else {
     file_list = fopen(argv[2], "r");
   }
   if (file_list) {
     while ((s = read_a_line(file_list))) {
       count_file(s);
       free(s);
     }
   }
 } else {
   for (i=1; i < argc; i++) { count_file(argv[i]); }
 }
 printf("Total:\n");
 printf("%ld\n", total_sloc);
 return 0;
}
