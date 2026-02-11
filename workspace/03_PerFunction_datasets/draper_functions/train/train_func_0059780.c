create_manager(GtkWindow* parent,
								const std::string& font_family_,
								int font_size_) {

  IntrusivePtr<TextPrintManager> instance_i(new TextPrintManager);
  instance_i->print_notifier.connect(Callback::make(*instance_i, &TextPrintManager::print_text));

  Thread::Mutex::Lock lock(instance_i->mutex);
  instance_i->parent_p = parent;
  instance_i->font_family = font_family_;
  instance_i->font_size = font_size_;
  instance_i->cancelled_when_drawing = false;
  instance_i->ready = true;

  return instance_i;
}
