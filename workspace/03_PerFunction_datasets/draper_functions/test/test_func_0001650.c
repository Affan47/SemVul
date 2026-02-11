FCEU_fclose(FCEUFILE *fp)
{
 if(fp->type==1)
 {
  gzclose(fp->fp);
 }
 else if(fp->type>=2)
 {
  free(((MEMWRAP*)(fp->fp))->data);
  free(fp->fp);
 }
 else
 {
  fclose((FILE *)fp->fp);
 }
 free(fp);
 return 1;
}
