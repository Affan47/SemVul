cb_view__i(Fl_Help_View*, void*) {
  if (view_->filename())
{
  if (view_->changed())
  {
    index_ ++;

    if (index_ >= 100)
    {
      memmove(line_, line_ + 10, sizeof(line_[0]) * 90);
      memmove(file_, file_ + 10, sizeof(file_[0]) * 90);
      index_ -= 10;
    }

    max_ = index_;

    strlcpy(file_[index_], view_->filename(),sizeof(file_[0]));
    line_[index_] = view_->topline();

    if (index_ > 0)
      back_->activate();
    else
      back_->deactivate();

    forward_->deactivate();
    window_->label(view_->title());
  }
  else
  {
    strlcpy(file_[index_], view_->filename(), sizeof(file_[0]));
    line_[index_] = view_->topline();
  }
} else {
  index_ = 0;
  file_[index_][0] = 0;
  line_[index_] = view_->topline();
  back_->deactivate();
  forward_->deactivate();
};
}
