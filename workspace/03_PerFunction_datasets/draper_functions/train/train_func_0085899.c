scintilla_class_init(ScintillaClass *klass) {
	try {
		OBJECT_CLASS *object_class = (OBJECT_CLASS*) klass;
		GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
		GtkContainerClass *container_class = (GtkContainerClass*) klass;

		GSignalFlags sigflags = GSignalFlags(G_SIGNAL_ACTION | G_SIGNAL_RUN_LAST);
		scintilla_signals[COMMAND_SIGNAL] = g_signal_new(
		            "command",
		            G_TYPE_FROM_CLASS(object_class),
		            sigflags,
		            G_STRUCT_OFFSET(ScintillaClass, command),
		            NULL,
		            NULL,
		            SIG_MARSHAL,
		            G_TYPE_NONE,
		            2, MARSHAL_ARGUMENTS);

		scintilla_signals[NOTIFY_SIGNAL] = g_signal_new(
		            SCINTILLA_NOTIFY,
		            G_TYPE_FROM_CLASS(object_class),
		            sigflags,
		            G_STRUCT_OFFSET(ScintillaClass, notify),
		            NULL,
		            NULL,
		            SIG_MARSHAL,
		            G_TYPE_NONE,
		            2, MARSHAL_ARGUMENTS);

		klass->command = NULL;
		klass->notify = NULL;

		ScintillaGTK::ClassInit(object_class, widget_class, container_class);
	} catch (...) {
	}
}
