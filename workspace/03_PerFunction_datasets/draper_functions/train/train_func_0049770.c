elm_smart_scroller_paging_set(Evas_Object *obj, double pagerel_h, double pagerel_v, Evas_Coord pagesize_h, Evas_Coord pagesize_v)
{
   API_ENTRY return;
   sd->pagerel_h = pagerel_h;
   sd->pagerel_v = pagerel_v;
   sd->pagesize_h = pagesize_h;
   sd->pagesize_v = pagesize_v;
   _smart_page_adjust(sd);
}
