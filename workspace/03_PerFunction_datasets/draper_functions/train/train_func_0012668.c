plot(char * title, char * subtitle, int balance_field,
         char * export_filename,
         int width, int height,
         char * image_filename)
{
  char command[STRING_BLOCK],data_filename[STRING_BLOCK];
  char xlabelstr[STRING_BLOCK],ylabelstr[STRING_BLOCK];
  FILE * fp;
  int retval=0;
  char * plot_filename = "gnuplot.plot";


  sprintf((char*)data_filename,"%s","gnuplot2.csv");
  trim_file_header(export_filename, data_filename);

  fp = fopen(plot_filename,"w");
  if (fp!=NULL) {


    fprintf(fp,"%s","reset\n");
    fprintf(fp,"set title \"%s\"\n",title);

    if (subtitle != NULL) {
      fprintf(fp,"set label \"%s\" at screen 0.47, screen 0.90\n",
              subtitle);
    }

    sprintf(xlabelstr,"%s",     get_text_from_identifier(DATE));
    xlabelstr[0] = toupper(xlabelstr[0]);

    sprintf(ylabelstr,"%s",     get_text_from_identifier(BALANCE));
    ylabelstr[0] = toupper(ylabelstr[0]);

    fprintf(fp,"%s","set lmargin 11\n");
    fprintf(fp,"%s","set rmargin 2\n");
    fprintf(fp,"set xlabel \"%s\"\n",xlabelstr);
    fprintf(fp,"set ylabel \"%s\"\n",ylabelstr);
    fprintf(fp,"%s","set grid\n");
    fprintf(fp,"%s","set key off\n");
    fprintf(fp,"%s","set xdata time\n");
    fprintf(fp,"%s","set timefmt \"%Y-%m\"\n");
    fprintf(fp,"%s","set format x \"%Y-%m\"\n");
    fprintf(fp,"set terminal png size %d,%d\n",width,height);
    fprintf(fp,"set output \"%s\"\n",image_filename);
    fprintf(fp,"plot \"%s\" using 1:%d with lines\n",
            data_filename,balance_field+1);

    fclose(fp);


    sprintf((char*)command,"gnuplot %s",plot_filename);
    retval=system(command);
    plot_cleanup();
  }
  return retval;
}
