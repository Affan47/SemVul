WriteHTMLFileDelete(char *name)
{
 FILE *in,*out;
 char line[256];
 int seen=0;
 char *inc_file,*ofile,*ifile;

 ofile=ConcatStrings(4,option_odir,"/",name,HTML_FILE);
 unlink(ofile);

 inc_file=ConcatStrings(6,"<a href=\"",name,HTML_FILE,"#file\">",name,"</a><br>\n");
 ifile=ConcatStrings(4,option_odir,"/",option_name,HTML_FILE);
 ofile=ConcatStrings(4,option_odir,"/",option_name,HTML_FILE_BACKUP);

 in =fopen(ifile,"r");
 out=fopen(ofile,"w");

 if(in && !out)
   {fprintf(stderr,"cxref: Failed to open the main HTML output file '%s'\n",ofile);fclose(in);}
 else if(in)
   {
    while(fgets(line,256,in))
      {
       if(!strcmp(inc_file,line) ||
          (!strncmp("<!--",line,4) && !strncmp(inc_file,line+4,strlen(inc_file)-1)) ||
          (!strncmp("<!-- ",line,5) && !strncmp(inc_file,line+5,strlen(inc_file)-1)))
          seen=1;
       else
          fputs(line,out);
      }

    fclose(in);
    fclose(out);

    if(seen)
      {
       unlink(ifile);
       rename(ofile,ifile);
      }
    else
       unlink(ofile);
   }
 else if(out)
   {
    fclose(out);
    unlink(ofile);
   }
}
