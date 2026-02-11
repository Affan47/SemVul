_e_qa_help5(void *data __UNUSED__)
{
   char buf[PATH_MAX];

   if (_e_qa_entry_find_border(qa_mod->demo_dia->win->border))
     {
        qa_mod->help_timer = ecore_timer_add(1, _e_qa_help_timer_cb, NULL);
        return;
     }

   if (qa_mod->help_dia)
     {
        ecore_job_add(_e_qa_help5, NULL);
        return;
     }
   snprintf(buf, sizeof(buf), "%s/e-module-quickaccess.edj", e_module_dir_get(qa_mod->module));
   qa_mod->help_dia = (E_Object*)e_confirm_dialog_show(_("Quickaccess Help"), buf,
                                                        _("You deleted it on your own, you rascal!<br>"
                                                          "Way to go!"),
                                                        _("Continue"), _("Stop"),
                                                        _e_qa_help6, _e_qa_help_cancel, NULL, NULL, NULL, NULL);
   e_object_free_attach_func_set(qa_mod->help_dia, _e_qa_dia_del);
}
