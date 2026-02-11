cph_mechanism_printer_delete (CphIfaceMechanism     *object,
                              GDBusMethodInvocation *context,
                              const char            *name)
{
        CphMechanism *mechanism = CPH_MECHANISM (object);
        gboolean      ret;

        _cph_mechanism_emit_called (mechanism);

        if (!_check_polkit_for_printer (mechanism, context, name, NULL))
                return TRUE;

        ret = cph_cups_printer_delete (mechanism->priv->cups, name);

        cph_iface_mechanism_complete_printer_delete (
                        object, context,
                        _cph_mechanism_return_error (mechanism, !ret));
        return TRUE;
}
