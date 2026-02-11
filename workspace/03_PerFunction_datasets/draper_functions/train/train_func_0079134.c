_e_qa_entry_border_props_apply(E_Quick_Access_Entry *entry)
{
   if (!entry->border) return;

   if (entry->config.autohide && (!entry->border->focused))
     _e_qa_border_deactivate(entry);
#define SET(X) \
   entry->border->X = 1
   if (entry->config.jump)
     {
        entry->border->client.netwm.state.skip_taskbar = 0;
        entry->border->client.netwm.state.skip_pager = 0;
     }
   else
     {
        if (qa_config->skip_taskbar)
          SET(client.netwm.state.skip_taskbar);
        if (qa_config->skip_pager)
          SET(client.netwm.state.skip_pager);
        SET(sticky);
     }

   SET(lock_user_iconify);
   SET(lock_client_iconify);
   SET(lock_user_sticky);
   SET(lock_client_sticky);
   SET(user_skip_winlist);
   SET(changed);
#undef SET
}
