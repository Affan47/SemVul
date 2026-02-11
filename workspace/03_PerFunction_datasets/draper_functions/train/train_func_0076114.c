DumpCMFlags(FILE *fp, CM_t *cm)
{
  fprintf(fp, "Dumping CM flags:\n");
  if(cm->flags & CMH_BITS)                 fprintf(fp, "\tCMH_BITS\n");
  if(cm->flags & CMH_ACC)                  fprintf(fp, "\tCMH_ACC\n");
  if(cm->flags & CMH_DESC)                 fprintf(fp, "\tCMH_DESC\n");
  if(cm->flags & CMH_RF)                   fprintf(fp, "\tCMH_RF\n");
  if(cm->flags & CMH_GA)                   fprintf(fp, "\tCMH_GA\n");
  if(cm->flags & CMH_TC)                   fprintf(fp, "\tCMH_TC\n");
  if(cm->flags & CMH_NC)                   fprintf(fp, "\tCMH_NC\n");
  if(cm->flags & CMH_CHKSUM)               fprintf(fp, "\tCMH_CHKSUM\n");
  if(cm->flags & CMH_MAP)                  fprintf(fp, "\tCMH_MAP\n");
  if(cm->flags & CMH_CONS)                 fprintf(fp, "\tCMH_CONS\n");
  if(cm->flags & CMH_LOCAL_BEGIN)          fprintf(fp, "\tCMH_LOCAL_BEGIN\n");
  if(cm->flags & CMH_LOCAL_END)            fprintf(fp, "\tCMH_LOCAL_END\n");
  if(cm->flags & CMH_EXPTAIL_STATS)        fprintf(fp, "\tCMH_EXPTAIL_STATS\n");
  if(cm->flags & CMH_CP9)                  fprintf(fp, "\tCMH_CP9\n");
  if(cm->flags & CMH_CP9_TRUNC)            fprintf(fp, "\tCMH_CP9_TRUNC\n");
  if(cm->flags & CMH_MLP7)                 fprintf(fp, "\tCMH_MLP7\n");
  if(cm->flags & CMH_FP7)                  fprintf(fp, "\tCMH_FP7\n");

  if(cm->flags & CM_IS_SUB)               fprintf(fp, "\tCM_IS_SUB\n");
  if(cm->flags & CM_IS_RSEARCH)           fprintf(fp, "\tCM_IS_RSEARCH\n");
  if(cm->flags & CM_RSEARCHTRANS)         fprintf(fp, "\tCM_RSEARCHTRANS\n");
  if(cm->flags & CM_RSEARCHEMIT)          fprintf(fp, "\tCM_RSEARCHEMIT\n");
  if(cm->flags & CM_EMIT_NO_LOCAL_BEGINS) fprintf(fp, "\tCM_EMIT_NO_LOCAL_BEGINS\n");
  if(cm->flags & CM_EMIT_NO_LOCAL_ENDS)   fprintf(fp, "\tCM_EMIT_NO_LOCAL_ENDS\n");

  fprintf(fp, "Finished dumping CM flags.\n");
  return;
}
