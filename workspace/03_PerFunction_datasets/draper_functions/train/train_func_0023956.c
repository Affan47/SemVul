find_device_node (GUPnPControlPoint *control_point,
                  const char        *udn)
{
        GList *l;

        l = control_point->priv->devices;

        while (l) {
                GUPnPDeviceInfo *info;

                info = GUPNP_DEVICE_INFO (l->data);

                if (strcmp (udn, gupnp_device_info_get_udn (info)) == 0)
                        break;

                l = l->next;
        }

        return l;
}
