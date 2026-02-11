generate_interface_xml(GString *gstr, struct interface_data *iface)
{
	const GDBusMethodTable *method;
	const GDBusSignalTable *signal;
	const GDBusPropertyTable *property;

	for (method = iface->methods; method && method->name; method++) {
		gboolean deprecated = method->flags &
						G_DBUS_METHOD_FLAG_DEPRECATED;
		gboolean noreply = method->flags &
						G_DBUS_METHOD_FLAG_NOREPLY;

		if (check_experimental(method->flags,
					G_DBUS_METHOD_FLAG_EXPERIMENTAL))
			continue;

		if (!deprecated && !noreply &&
				!(method->in_args && method->in_args->name) &&
				!(method->out_args && method->out_args->name))
			g_string_append_printf(gstr,
						"\t\t<method name=\"%s\"/>\n",
						method->name);
		else {
			g_string_append_printf(gstr,
						"\t\t<method name=\"%s\">\n",
						method->name);
			print_arguments(gstr, method->in_args, "in");
			print_arguments(gstr, method->out_args, "out");

			if (deprecated)
				g_string_append_printf(gstr,
					G_DBUS_ANNOTATE_DEPRECATED("\t\t\t"));
			if (noreply)
				g_string_append_printf(gstr,
					G_DBUS_ANNOTATE_NOREPLY("\t\t\t"));

			g_string_append_printf(gstr, "\t\t</method>\n");
		}
	}

	for (signal = iface->signals; signal && signal->name; signal++) {
		gboolean deprecated = signal->flags &
						G_DBUS_SIGNAL_FLAG_DEPRECATED;

		if (check_experimental(signal->flags,
					G_DBUS_SIGNAL_FLAG_EXPERIMENTAL))
			continue;

		if (!deprecated && !(signal->args && signal->args->name))
			g_string_append_printf(gstr,
						"\t\t<signal name=\"%s\"/>\n",
						signal->name);
		else {
			g_string_append_printf(gstr,
						"\t\t<signal name=\"%s\">\n",
						signal->name);
			print_arguments(gstr, signal->args, NULL);

			if (deprecated)
				g_string_append_printf(gstr,
					G_DBUS_ANNOTATE_DEPRECATED("\t\t\t"));

			g_string_append_printf(gstr, "\t\t</signal>\n");
		}
	}

	for (property = iface->properties; property && property->name;
								property++) {
		gboolean deprecated = property->flags &
					G_DBUS_PROPERTY_FLAG_DEPRECATED;

		if (check_experimental(property->flags,
					G_DBUS_PROPERTY_FLAG_EXPERIMENTAL))
			continue;

		g_string_append_printf(gstr, "\t\t<property name=\"%s\""
					" type=\"%s\" access=\"%s%s\"",
					property->name,	property->type,
					property->get ? "read" : "",
					property->set ? "write" : "");

		if (!deprecated)
			g_string_append_printf(gstr, "/>\n");
		else
			g_string_append_printf(gstr,
				G_DBUS_ANNOTATE_DEPRECATED(">\n\t\t\t"));
	}
}
