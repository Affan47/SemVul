WriteLatexDocument(char* name,int appendix)
{
 FILE *in,*out;
 char line[256];
 int seen=0;
 char *inc_file,*ofile,*ifile;

 inc_file=ConcatStrings(4,"\\input{",name,LATEX_FILE,"}\n");
 ifile=ConcatStrings(4,option_odir,"/",option_name,LATEX_FILE);
 ofile=ConcatStrings(4,option_odir,"/",option_name,LATEX_FILE_BACKUP);

 in =fopen(ifile,"r");
 if(!in)
   {
    WriteLatexTemplate(ifile);
    in =fopen(ifile,"r");
   }

 out=fopen(ofile,"w");

 if(!out)
   {fprintf(stderr,"cxref: Failed to open the main LaTeX output file '%s'\n",ofile);exit(1);}

 while(fgets(line,256,in))
   {
    if(!strcmp(inc_file,line) ||
       (line[0]=='%' && !strcmp(inc_file,line+1)) ||
       (line[0]=='%' && line[1]==' ' && !strcmp(inc_file,line+2)))
       {seen=1;break;}
    if(line[0]=='%' && !strcmp("% End-Of-Source-Files\n",line))
      {
       if(appendix)
         {
          fputs(line,out);
          fputs("\n",out);
          fputs("% Appendix\n",out);
          fputs("\n",out);
          fputs("\\appendix\n",out);
          fputs("\\markboth{Appendix}{Appendix}\n",out);
          fputs(inc_file,out);
         }
       else
         {
          fputs(inc_file,out);
          fputs("\n",out);
          fputs(line,out);
         }
      }
    else
       fputs(line,out);
   }

 fclose(in);
 fclose(out);

 if(!seen)
   {
    unlink(ifile);
    rename(ofile,ifile);
   }
 else
    unlink(ofile);
}
