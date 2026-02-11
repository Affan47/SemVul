free() {
    delete name_;
    delete dir_;
    delete filter_map_;
    Resource::unref(action_);
    style_->remove_trigger_any(update_);
    Resource::unref(style_);
}
