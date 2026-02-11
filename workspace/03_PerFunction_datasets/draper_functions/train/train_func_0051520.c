sge_gdi_packet_pack_task(sge_gdi_packet_class_t *packet,
                         sge_gdi_task_class_t *task, lList **answer_list,
                         sge_pack_buffer *pb)
{
   bool ret = true;
   int pack_ret = PACK_SUCCESS;

   DENTER(TOP_LAYER, "sge_gdi_packet_pack_task");

   if ((task != NULL) && (packet != NULL)
       && (packet->is_intern_request == false)) {
      sge_pack_gdi_info(task->command);


      pack_ret = packint(pb, task->command);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = packint(pb, task->target);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = packint(pb, packet->version);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }


      if (task->do_select_pack_simultaneous) {
         lSelectHashPack("", task->data_list, task->condition,
                         task->enumeration, false, pb);
         lFreeWhat(&(task->enumeration));
         lFreeWhere(&(task->condition));
         task->data_list = NULL;


         answer_list_add(&(task->answer_list), MSG_GDI_OKNL, STATUS_OK,
                         ANSWER_QUALITY_END);
      } else {

         pack_ret = cull_pack_list(pb, task->data_list);
         if (pack_ret != PACK_SUCCESS) {
            goto error_with_mapping;
         }
      }


      pack_ret = cull_pack_list(pb, task->answer_list);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = cull_pack_cond(pb, task->condition);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = cull_pack_enum(pb, task->enumeration);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = packstr(pb, packet->auth_info);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = packint(pb, task->id);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = packint(pb, packet->id);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
      pack_ret = packint(pb, (task->next != NULL) ? 1 : 0);
      if (pack_ret != PACK_SUCCESS) {
         goto error_with_mapping;
      }
   }

   DRETURN(ret);
 error_with_mapping:
   ret = sge_gdi_map_pack_errors(pack_ret, answer_list);
   DRETURN(ret);
}
