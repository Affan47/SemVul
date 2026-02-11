TexinfoSubBodyParts(FILE *fout,struct BodySyntax *bs)

{ int i;
 char filename[CF_BUFSIZE],*res;

if (bs == NULL)
   {
   return;
   }

fprintf(fout,"@table @samp\n");

for (i = 0; bs[i].lval != NULL; i++)
   {
   if (bs[i].range == (void *)CF_BUNDLE)
      {
      fprintf(fout,"@item @code{%s}\n@b{Type}: %s\n (Separate Bundle) \n\n",bs[i].lval,CF_DATATYPES[bs[i].dtype]);
      }
   else if (bs[i].dtype == cf_body)
      {
      fprintf(fout,"@item @code{%s}\n@b{Type}: %s\n\n",bs[i].lval,CF_DATATYPES[bs[i].dtype]);
      TexinfoSubBodyParts(fout,(struct BodySyntax *)bs[i].range);
      }
   else
      {
      fprintf(fout,"@item @code{%s}\n@b{Type}: %s\n\n",bs[i].lval,CF_DATATYPES[bs[i].dtype]);
      TexinfoShowRange(fout,(char *)bs[i].range,bs[i].dtype);
      fprintf(fout,"\n@noindent @b{Synopsis}: %s\n\n",bs[i].description);

      if ((res = GetControlDefault(bs[i].lval)))
         {
         fprintf(fout,"\n@noindent @b{Default value:} %s\n",res);
         }
      else if ((res = GetBodyDefault(bs[i].lval)))
         {
         fprintf(fout,"\n@noindent @b{Default value:} %s\n",res);
         }

      fprintf(fout,"\n@b{Example}:@*\n");
      snprintf(filename,CF_BUFSIZE-1,"bodypart_%s_example.texinfo",bs[i].lval);
      IncludeManualFile(fout,filename);
      fprintf(fout,"\n@b{Notes}:@*\n");
      snprintf(filename,CF_BUFSIZE-1,"bodypart_%s_notes.texinfo",bs[i].lval);
      IncludeManualFile(fout,filename);
      }
   }

fprintf(fout,"@end table\n");
}
