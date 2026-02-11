slotInterfacesAdded(const QDBusObjectPath& object_path, const QVariantMapMap& interfaces_and_properties)
{
    if (object_path.path() != m_udi) {
        return;
    }

    Q_FOREACH(const QString & iface, interfaces_and_properties.keys()) {

        if (iface.startsWith(UD2_DBUS_SERVICE)) {
            m_interfaces.append(interfaces_and_properties.keys());
        }
    }
}
