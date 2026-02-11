ege_output_action_class_init( EgeOutputActionClass* klass )
{
    if ( klass ) {
        GObjectClass* objClass = G_OBJECT_CLASS( klass );
        gParentClass = GTK_ACTION_CLASS( g_type_class_peek_parent( klass ) );

        objClass->get_property = ege_output_action_get_property;
        objClass->set_property = ege_output_action_set_property;


        klass->parent_class.create_tool_item = create_tool_item;

        g_object_class_install_property( objClass,
                                         PROP_USE_MARKUP,
                                         g_param_spec_boolean( "use-markup",
                                                               "UseMarkup",
                                                               "If markup should be used",
                                                               FALSE,
                                                               (GParamFlags)(G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT) ) );

        g_type_class_add_private( klass, sizeof(EgeOutputActionClass) );
    }
}
