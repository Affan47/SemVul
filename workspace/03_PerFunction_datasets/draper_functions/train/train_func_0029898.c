auto_detect_action (GPParams *p)
{
	int x, count;
        CameraList *list;
        const char *name = NULL, *value = NULL;

	_get_portinfo_list (p);
	count = gp_port_info_list_count (p->portinfo_list);

	CR (gp_list_new (&list));
        gp_abilities_list_detect (gp_params_abilities_list(p), p->portinfo_list, list, p->context);

        CL (count = gp_list_count (list), list);

        printf(_("%-30s %-16s\n"), _("Model"), _("Port"));
        printf(_("----------------------------------------------------------\n"));
        for (x = 0; x < count; x++) {
                CL (gp_list_get_name  (list, x, &name), list);
                CL (gp_list_get_value (list, x, &value), list);
                printf(_("%-30s %-16s\n"), name, value);
        }
	gp_list_free (list);
        return GP_OK;
}
