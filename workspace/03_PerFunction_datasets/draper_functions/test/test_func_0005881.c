Q_PushHead(queue *q, void *d)
{
      node    *n = NULL;
      datanode *p;


      if (q->head == NULL)
      {
            q->head = malloc(sizeof(datanode));
            if (q->head == NULL)
                  return False_;
      }
      else
      {

            q->head->prev = malloc(sizeof(datanode));
            if (q->head->prev == NULL)
                  return False_;

            n = q->head;

            p = q->head->prev;
            q->head = (node*)p;
      }
      q->head->prev = NULL;

      if (q->size == 0)
      {
            q->head->next = NULL;
            q->tail = q->head;
      }
      else  q->head->next = (datanode*)n;

      q->head->data = d;
      q->size++;

      q->cursor = q->head;

      q->sorted = False_;

      return True_;
}
