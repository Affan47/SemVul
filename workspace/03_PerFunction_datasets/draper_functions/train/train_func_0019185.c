query_new_value(struct hud_graph *gr)
{
   struct query_info *info = gr->query_data;
   struct pipe_context *pipe = info->pipe;
   uint64_t now = os_time_get();

   if (info->last_time) {
      pipe->end_query(pipe, info->query[info->head]);


      while (1) {
         struct pipe_query *query = info->query[info->tail];
         union pipe_query_result result;
         uint64_t *res64 = (uint64_t *)&result;

         if (pipe->get_query_result(pipe, query, FALSE, &result)) {
            info->results_cumulative += res64[info->result_index];
            info->num_results++;

            if (info->tail == info->head)
               break;

            info->tail = (info->tail+1) % NUM_QUERIES;
         }
         else {

            if ((info->head+1) % NUM_QUERIES == info->tail) {


               fprintf(stderr,
                       "gallium_hud: all queries are busy after %i frames, "
                       "can't add another query\n",
                       NUM_QUERIES);
               pipe->destroy_query(pipe, info->query[info->head]);
               info->query[info->head] =
                     pipe->create_query(pipe, info->query_type);
            }
            else {


               info->head = (info->head+1) % NUM_QUERIES;
               if (!info->query[info->head]) {
                  info->query[info->head] =
                        pipe->create_query(pipe, info->query_type);
               }
            }
            break;
         }
      }

      if (info->num_results && info->last_time + gr->pane->period <= now) {

         hud_graph_add_value(gr, info->results_cumulative / info->num_results);

         info->last_time = now;
         info->results_cumulative = 0;
         info->num_results = 0;
      }

      pipe->begin_query(pipe, info->query[info->head]);
   }
   else {

      info->last_time = now;
      info->query[info->head] = pipe->create_query(pipe, info->query_type);
      pipe->begin_query(pipe, info->query[info->head]);
   }
}
