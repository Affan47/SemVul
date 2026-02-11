gt_text_width_calculator_get_text_width(GtTextWidthCalculator *twc,
                                               const char* text,
                                               GtError *err)
{
  double width;
  gt_assert(twc && text);
  gt_rwlock_rdlock(twc->pvt->lock);
  gt_assert(twc->c_class);
  width = twc->c_class->get_text_width(twc, text, err);
  gt_rwlock_unlock(twc->pvt->lock);
  return width;
}
