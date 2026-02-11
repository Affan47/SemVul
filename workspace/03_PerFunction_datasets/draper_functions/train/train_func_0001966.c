_e_qa_help(void *data)
{
   char buf[PATH_MAX];

   if (data && qa_mod->help_dia)
     {
        ecore_job_add(_e_qa_help, (void*)1);
        return;
     }
   if (qa_mod->help_dia) return;
   snprintf(buf, sizeof(buf), "%s/e-module-quickaccess.edj", e_module_dir_get(qa_mod->module));
   qa_mod->help_dia = (E_Object*)e_confirm_dialog_show(_("Quickaccess Help"), buf,
                                                        _("Quickaccess is a way of binding user-selected<br>"
                                                          "windows and applications to keyboard shortcuts.<br>"
                                                          "Once a Quickaccess entry has been created,<br>"
                                                          "the associated window can be returned to immediately<br>"
                                                          "on demand by pushing the keyboard shortcut."),
                                                        _("Continue"), _("Stop"),
                                                        _e_qa_help2, _e_qa_help_cancel, NULL, NULL, NULL, NULL);
   e_object_free_attach_func_set(qa_mod->help_dia, _e_qa_dia_del);
}
