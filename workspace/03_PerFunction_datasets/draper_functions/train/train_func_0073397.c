um_realm_join_finish (UmRealmObject *realm,
                      GAsyncResult *result,
                      GError **error)
{
        UmRealmKerberosMembership *membership;
        GError *call_error = NULL;
        gchar *dbus_error;
        GAsyncResult *async;

        g_return_val_if_fail (UM_REALM_IS_OBJECT (realm), FALSE);
        g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

        membership = um_realm_object_get_kerberos_membership (realm);
        g_return_val_if_fail (membership != NULL, FALSE);

        async = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (result));
        um_realm_kerberos_membership_call_join_finish (membership, async, &call_error);
        g_object_unref (membership);

        if (call_error == NULL)
                return TRUE;

        dbus_error = g_dbus_error_get_remote_error (call_error);
        if (dbus_error == NULL) {
                g_debug ("Join() failed because of %s", call_error->message);
                g_propagate_error (error, call_error);
                return FALSE;
        }

        g_dbus_error_strip_remote_error (call_error);

        if (g_str_equal (dbus_error, "org.freedesktop.realmd.Error.AuthenticationFailed")) {
                g_debug ("Join() failed because of invalid/insufficient credentials");
                g_set_error (error, UM_REALM_ERROR, UM_REALM_ERROR_BAD_LOGIN,
                             "%s", call_error->message);
                g_error_free (call_error);
        } else {
                g_debug ("Join() failed because of %s", call_error->message);
                g_propagate_error (error, call_error);
        }

        g_free (dbus_error);
        return FALSE;
}
