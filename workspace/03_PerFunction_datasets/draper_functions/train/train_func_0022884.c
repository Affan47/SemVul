RemoveAllStaticRenderedViews() {
  for (StaticRenderedViews::iterator it = static_rendered_views_.begin();
       it != static_rendered_views_.end(); ++it) {
    delete it->renderer;
  }
  static_rendered_views_.clear();
}
