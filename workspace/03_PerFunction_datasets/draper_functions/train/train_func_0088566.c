_elm_gengrid_item_del_not_serious(Elm_Gen_Item *it)
{
   elm_widget_item_pre_notify_del(it);
   it->generation = GG_IT(it)->wsd->generation - 1;


   if ((it->relcount > 0) || (it->walking > 0)) return;

   if (it->selected)
     GG_IT(it)->wsd->selected =
       eina_list_remove(GG_IT(it)->wsd->selected, it);

   if (it->itc->func.del)
     it->itc->func.del((void *)it->base.data, WIDGET(it));
}
