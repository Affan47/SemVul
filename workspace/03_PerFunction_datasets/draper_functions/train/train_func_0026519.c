categorize_ijekjoik(TreeNode *head)
{
  TreeNode *x, *marker;

  for (x = head->next; x!=head; x=x->next) {
    if ((x->type == N_CMAVO) &&
        (x->data.cmavo.selmao == I)) {

      if ((x->prev->type == N_MARKER) &&
          (x->prev->data.marker.tok == PRIVATE_I_BO)) {

      } else {
        if ((x->next->type == N_MARKER) &&
            ((x->next->data.marker.tok == PRIVATE_START_JEK) ||
             (x->next->data.marker.tok == PRIVATE_START_JOIK))) {
          marker = new_node();
          marker->type = N_MARKER;
          marker->start_line = x->start_line;
          marker->start_column = x->start_column;
          marker->data.marker.tok = PRIVATE_I_JEKJOIK;
          marker->data.marker.text = new_string("PRIVATE_I_JEKJOIK");

          marker->prev = x->prev;
          marker->next = x;
          x->prev->next = marker;
          x->prev = marker;
        }
      }
    }
  }
}
