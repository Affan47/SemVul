_e_fm2_cb_dnd_selection_notify_post_mount_fail(E_Volume *vol)
{
   E_Fm2_Device_Mount_Op *mop;

   while (vol->mount_ops)
     {
        E_Fm2_Icon *ic;

        mop = (E_Fm2_Device_Mount_Op*) vol->mount_ops;
        ic = mop->ic;
        vol->mount_ops = eina_inlist_remove(vol->mount_ops, EINA_INLIST_GET(mop));

        e_util_dialog_show(_("Error"), _("The recent DND operation requested for '%s' has failed."), vol->label ?: vol->udi);
        evas_object_data_del(ic->sd->obj, "dnd_queue");
        free(mop->args);
        ic->sd->mount_ops = eina_list_remove(ic->sd->mount_ops, mop);
        free(mop);
     }
}
