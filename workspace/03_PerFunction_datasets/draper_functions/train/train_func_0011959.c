update_skg (GtkSatModule *module)
{


    if G_UNLIKELY(fabs(module->tmgCdnum - module->lastSkgUpd) > 7.0e-4) {

        sat_log_log (SAT_LOG_LEVEL_MSG,
                     _("%s: Updating GtkSkyGlance for %s"),
                     __FUNCTION__, module->name);

        gtk_container_remove (GTK_CONTAINER (module->skgwin), module->skg);
        module->skg = gtk_sky_glance_new (module->satellites, module->qth, module->tmgCdnum);
        gtk_container_add (GTK_CONTAINER (module->skgwin), module->skg);
        gtk_widget_show_all (module->skg);

        module->lastSkgUpd = module->tmgCdnum;
    }
}
