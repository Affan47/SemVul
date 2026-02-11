done(GtkPrintOperation* print_operation_p,
		   GtkPrintOperationResult result,
		   void* data) {

    Cgu::TextPrintManager* instance_p = static_cast<Cgu::TextPrintManager*>(data);
    if (result == GTK_PRINT_OPERATION_RESULT_ERROR) {
      GError* error_p = 0;
      gtk_print_operation_get_error(print_operation_p, &error_p);
      if (error_p) {
	Cgu::GerrorScopedHandle handle_h(error_p);
	g_warning("CguTextPrintManagerCB::text_print_done(): %s\n", error_p->message);
      }
    }
    else if (result == GTK_PRINT_OPERATION_RESULT_APPLY) {

      Cgu::TextPrintManager::print_settings_h =
	Cgu::GobjHandle<GtkPrintSettings>(gtk_print_operation_get_print_settings(print_operation_p));

      g_object_ref(G_OBJECT(Cgu::TextPrintManager::print_settings_h.get()));
    }
    else if (result == GTK_PRINT_OPERATION_RESULT_CANCEL
	     && instance_p->parent_p
	     && !instance_p->cancelled_when_drawing) {


      gtk_widget_set_sensitive(GTK_WIDGET(instance_p->parent_p), true);
    }
    {
      Cgu::Thread::Mutex::Lock lock(instance_p->mutex);
      instance_p->ready = true;
    }
    instance_p->unref();
  }
