_e_qa_bd_menu_jump(void *data, E_Menu *m __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Quick_Access_Entry *entry = data;

   entry->config.jump = !entry->config.jump;
   if (entry->config.jump)
     {
        entry->config.autohide = entry->config.hide_when_behind = 0;
        _e_qa_entry_border_props_restore(entry, entry->border);
     }
   else
     _e_qa_entry_border_props_apply(entry);
}
