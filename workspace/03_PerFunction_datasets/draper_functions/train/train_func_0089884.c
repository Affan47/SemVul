_split_strict(list_t *dirty, const rect_t current, rect_t r)
{
   int h_1, h_2, w_1, w_2;

   h_1 = current.top - r.top;
   h_2 = r.bottom - current.bottom;
   w_1 = current.left - r.left;
   w_2 = r.right - current.right;

   if (h_1 > 0)
     {


        rect_list_append_xywh(dirty, r.left, r.top, r.width, h_1);
        r.height -= h_1;
        r.top = current.top;
     }

   if (h_2 > 0)
     {


        rect_list_append_xywh(dirty, r.left, current.bottom, r.width, h_2);
        r.height -= h_2;
     }

   if (w_1 > 0)
     {


        rect_list_append_xywh(dirty, r.left, r.top, w_1, r.height);


     }

   if (w_2 > 0)
     {


        rect_list_append_xywh(dirty, current.right, r.top, w_2, r.height);


     }
}
