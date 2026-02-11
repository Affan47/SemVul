textsize(uchar s) {
  view_->textsize(s);

if (s <= 8)
  smaller_->deactivate();
else
  smaller_->activate();

if (s >= 18)
  larger_->deactivate();
else
  larger_->activate();
}
