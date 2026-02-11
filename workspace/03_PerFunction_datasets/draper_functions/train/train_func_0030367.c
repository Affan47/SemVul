categorize_number_roi(TreeNode *head) {

  TreeNode *x, *y, *marker;
  int count;

  for (x = head->next; x!=head; x=x->next) {
    if (x->type == N_CMAVO &&
        x->data.cmavo.selmao == ROI) {
      y = x->prev;
      count = 0;
      while (1) {
        if (y == head) goto done;

        if (y->type == N_MARKER) {
          y = y->prev;
        } else if (y->type == N_CMAVO) {
          switch (y->data.cmavo.selmao) {
            case PA:
            case BU:
            case BY:
            case LAU:
            case TEI:
            case FOI:
              count++;
              y = y->prev;
              break;

            default:
              goto done;
          }
        } else if (y->type == N_BU) {
          count++;
          y = y->prev;
        } else {
          goto done;
        }
      }

        done:

      if (count > 0) {
        marker = new_node();
        marker->type = N_MARKER;
        marker->start_line = y->start_line;
        marker->start_column = y->start_column;
        marker->data.marker.tok = PRIVATE_NUMBER_ROI;
        marker->data.marker.text = new_string("PRIVATE_NUMBER_ROI");
        marker->prev = y;
        marker->next = y->next;
        y->next->prev = marker;
        y->next = marker;
      }
    }
  }
}
