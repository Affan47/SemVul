daemon_create_user_authorized_cb (Daemon                *daemon,
                                  User                  *dummy,
                                  GDBusMethodInvocation *context,
                                  gpointer               data)

{
        CreateUserData *cd = data;
        User *user;
        GError *error;
        const gchar *argv[9];

        if (getpwnam (cd->user_name) != NULL) {
                throw_error (context, ERROR_USER_EXISTS, "A user with name '%s' already exists", cd->user_name);

                return;
        }

        sys_log (context, "create user '%s'", cd->user_name);

        argv[0] = "/usr/sbin/adduser";
        argv[1] = "--quiet";
        argv[2] = "--disabled-login";
        argv[3] = "--gecos";
        argv[4] = cd->real_name;
        argv[5] = cd->user_name;
        argv[6] = NULL;

        error = NULL;
        if (!spawn_with_login_uid (context, argv, &error)) {
                throw_error (context, ERROR_FAILED, "running '%s' failed: %s", argv[0], error->message);
                g_error_free (error);
                return;
        }

        if (cd->account_type == ACCOUNT_TYPE_ADMINISTRATOR) {
                add_user_to_group (context, cd->user_name, ADMIN_GROUP);
		 add_user_to_group (context, cd->user_name, "adm");
		 add_user_to_group (context, cd->user_name, "lpadmin");
		 add_user_to_group (context, cd->user_name, "sambashare");
        }

        user = daemon_local_find_user_by_name (daemon, cd->user_name);
        user_update_local_account_property (user, TRUE);
        user_update_system_account_property (user, FALSE);

        cache_user (daemon, user);

        accounts_accounts_complete_create_user (NULL, context, user_get_object_path (user));
}
