ck_session_constructor (GType                  type,
                        guint                  n_construct_properties,
                        GObjectConstructParam *construct_properties)
{
        CkSession      *session;
        CkSessionClass *klass;

        klass = CK_SESSION_CLASS (g_type_class_peek (CK_TYPE_SESSION));

        session = CK_SESSION (G_OBJECT_CLASS (ck_session_parent_class)->constructor (type,
                                                                                     n_construct_properties,
                                                                                     construct_properties));
        if (session_is_text (session)) {
                session_add_activity_watch (session);
        }

        return G_OBJECT (session);
}
