pf_log(int logsev, struct parse_frame *pf)
{
   int idx;

   LOG_FMT(logsev, "[%s] BrLevel=%d Level=%d PseTos=%d\n",
           get_token_name(pf->in_ifdef),
           pf->brace_level, pf->level, pf->pse_tos);

   LOG_FMT(logsev, " *");
   for (idx = 1; idx <= pf->pse_tos; idx++)
   {
      LOG_FMT(logsev, " [%s-%d]",
              get_token_name(pf->pse[idx].type),
              pf->pse[idx].stage);
   }
   LOG_FMT(logsev, "\n");
}
