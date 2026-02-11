lp_scene_queue_create(void)
{
   struct lp_scene_queue *queue = CALLOC_STRUCT(lp_scene_queue);
   if (queue == NULL)
      return NULL;

   queue->ring = util_ringbuffer_create( MAX_SCENE_QUEUE *
                                         sizeof( struct scene_packet ) / 4);
   if (queue->ring == NULL)
      goto fail;

   return queue;

fail:
   FREE(queue);
   return NULL;
}
