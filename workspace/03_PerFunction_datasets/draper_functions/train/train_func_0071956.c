serial_loop(WORKER_INFO *info, P7_HMMFILE *hfp)
{
  int            status;

  P7_OPROFILE   *om;
  ESL_ALPHABET  *abc = NULL;


  while ((status = p7_oprofile_ReadMSV(hfp, &abc, &om)) == eslOK)
    {
      p7_pli_NewModel(info->pli, om, info->bg);
      p7_bg_SetLength(info->bg, info->qsq->n);
      p7_oprofile_ReconfigLength(om, info->qsq->n);

      p7_Pipeline(info->pli, om, info->bg, info->qsq, info->th);

      p7_oprofile_Destroy(om);
      p7_pipeline_Reuse(info->pli);
    }

  esl_alphabet_Destroy(abc);

  return status;
}
