StateChange() {
    bool was_active = active_;
    active_ = uv_is_active((uv_handle_t*) &handle_);

    if (!was_active && active_) {


      uv_ref(uv_default_loop());
    } else if (was_active && !active_) {


      uv_unref(uv_default_loop());
    }
  }
