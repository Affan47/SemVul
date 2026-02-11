_cb_delete(void *data, void *data2 __UNUSED__)
{
   Del_Profile_Confirm_Data *d;
   char buf[4096];

   if (!data) return;

   d = E_NEW(Del_Profile_Confirm_Data, 1);
   d->cfdata = data;

   snprintf(buf, sizeof(buf),
            _("You want to delete the \"%s\" profile.<br><br>"
              "Are you sure?"), d->cfdata->sel_profile);
   e_confirm_dialog_show(_("Are you sure you want to delete this profile?"),
                         "dialog-warning", buf, _("Delete"), _("Keep"),
                         _cb_dialog_yes, NULL, d, NULL,
                         _cb_dialog_destroy, d);
}
