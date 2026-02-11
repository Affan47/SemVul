sge_gdi_map_pack_errors(int pack_ret, lList **answer_list)
{
   bool ret = true;

   DENTER(GDI_LAYER, "sge_gdi_map_pack_errors");
   switch (pack_ret) {
   case PACK_SUCCESS:
      break;
   case PACK_ENOMEM:
      answer_list_add_sprintf(answer_list, STATUS_ERROR2,
                              ANSWER_QUALITY_ERROR,
                              MSG_GDI_MEMORY_NOTENOUGHMEMORYFORPACKINGGDIREQUEST);
      break;
   case PACK_FORMAT:
      answer_list_add_sprintf(answer_list, STATUS_ERROR3,
                              ANSWER_QUALITY_ERROR,
                              MSG_GDI_REQUESTFORMATERROR);
      break;
   default:
      answer_list_add_sprintf(answer_list, STATUS_ERROR1,
                              ANSWER_QUALITY_ERROR,
                              MSG_GDI_UNEXPECTEDERRORWHILEPACKINGGDIREQUEST);
      break;
   }
   ret = (pack_ret == PACK_SUCCESS) ? true : false;

   DRETURN(ret);
}
